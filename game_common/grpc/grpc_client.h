#pragma once 

#include <google/protobuf/message.h>
#include <grpcpp/grpcpp.h>
#include <boost/asio.hpp>
#include <iostream>
#include <queue>

using grpc::Channel;
using grpc::ClientAsyncReader;
using grpc::ClientAsyncReaderWriter;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::CompletionQueue;
using grpc::Status;

using RespCb =
    std::function<void(uint64 uid, ::google::protobuf::Message* msg)>;

class Player;
// struct for keeping state and data information
class IAsyncClientCall : public std::enable_shared_from_this<IAsyncClientCall> {
 public:
  IAsyncClientCall() {}
  IAsyncClientCall(uint64 uid, std::string& moudle_name) : uid_(uid), moudle_name_(moudle_name) { msg_id_ = 0; }
  IAsyncClientCall(uint64 uid) : uid_(uid) { msg_id_ = 0; }

  virtual ~IAsyncClientCall() { Remove(); };

  virtual bool Run(int cbState = 0) { return true; };

  virtual void Start() {}

  virtual void StartNewClone() {}

  virtual void Finish() {}

  uint64 GetMsgId() {
    return ((++msg_id_ >= 0xFFFFFFFFFFFFFFFF) ? 1 : msg_id_);
  }

  void Remove() { TryCancel(); }

  void TryCancel() { context_.TryCancel(); }

  //   static void* Tag(IAsyncClientCall* c) { return static_cast<void*>(c); }
  //
  //   static IAsyncClientCall* DeTag(void* t) {
  //     return static_cast<IAsyncClientCall*>(t);
  //   }

  grpc::ClientContext& GetContext() { return context_; }
  grpc::Status& GetStatus() { return status_; }
  uint64 GetPlayerId() { return uid_; }
  const std::string& name() {return moudle_name_;}

 protected:
  ClientContext context_;
  Status status_;

 private:
  uint64 uid_;
  uint64 msg_id_;
  std::string moudle_name_; // 模块功能名称 测试log输出用
};

class StreamMessageTag {
 public:
  StreamMessageTag(int state, std::shared_ptr<IAsyncClientCall> call)
      : cb_state_(state), client_call_(call) {}
  ~StreamMessageTag() { client_call_ = nullptr; }

  static void* Tag(StreamMessageTag* c) { return static_cast<void*>(c); }
  static StreamMessageTag* DeTag(void* t) {
    return static_cast<StreamMessageTag*>(t);
  }

 public:
  int cb_state_;
  /*  uint64 message_id_;*/
  std::shared_ptr<IAsyncClientCall> client_call_;
};

template <class R>
class AsyncClientUnaryCall final : public IAsyncClientCall {
 public:
  typedef std::shared_ptr<ClientAsyncResponseReader<R>> read_ptr;

  AsyncClientUnaryCall(uint64 uid, RespCb&& func,
                       std::shared_ptr<boost::asio::io_context>& io)
      : IAsyncClientCall(uid),
        cb_(std::move(func)),
        io_(io),
        reply_(),
        next_state_(State::READY) {}

  virtual ~AsyncClientUnaryCall() override{};

  void Start() { Run(State::READY); }

  void DoFinish() {
    StreamMessageTag* msg =
        new StreamMessageTag(State::RESP_DONE, this->shared_from_this());
    reply_.Clear();
    response_reader_->Finish(&reply_, &status_, StreamMessageTag::Tag(msg));
  }

  void PostMsg() {
    auto self(shared_from_this());
    boost::asio::post(*io_, [this, self]() { cb_(GetPlayerId(), &reply_); });
  }

  bool Run(int cbState) override {
    switch (next_state_) {
      case State::READY:
        next_state_ = State::RESP_DONE;
        DoFinish();
        return true;
      case State::RESP_DONE:
        if (!status_.ok()) {
          return false;
        }
        PostMsg();
        next_state_ = State::INVALID;
        return false;
      default:
        return false;
    }
  }

  void set_reader(read_ptr pRpc) { response_reader_.swap(pRpc); }

  void StartNewClone() override {
    boost::asio::post(*io_, [&]() {
      AsyncClientUnaryCall* clone =
          new AsyncClientUnaryCall(GetPlayerId(), std::move(cb_), io_);
    });
  }

 public:
  read_ptr response_reader_;
  R reply_;

 private:
  RespCb cb_;
  std::shared_ptr<boost::asio::io_context> io_;
  enum State { INVALID, READY, RESP_DONE };
  State next_state_;
};

//聊天采用流式
template <class R, class W, class FUNC>
class AsyncRWStreamCall : public IAsyncClientCall {
 public:
  typedef std::shared_ptr<ClientAsyncReaderWriter<R, W>> stream_ptr;
  AsyncRWStreamCall(uint64 uid, const std::shared_ptr<FUNC>& func,
                    std::shared_ptr<boost::asio::io_context>& io,
	  std::string moudle_name = "")
      : IAsyncClientCall(uid, moudle_name), cb_(func), io_(io) {
    cur_state_ = State::INVALID;
    to_finish_ = is_finished_ = false;
    messages_waiting_ = msg_write_waiting_ = 0;
  }

  virtual ~AsyncRWStreamCall() override { req_list_.clear(); };

  void SetStream(stream_ptr pRpc) { stream_.swap(pRpc); }

  void Start() override { StartInternal(100); }

  bool WriteMsg(const std::shared_ptr<R>& req) {
    if (to_finish_ || req == nullptr) return false;
    topic = req->topic();
    DoWrite(std::move(req));

    return true;
  }

  void Finish() override {
    // assert(!to_finish_); //已调用结束，不能再次结束
    if (to_finish_) {
      return;
    }
    DoWriteDone();
    to_finish_ = true;  //!!!Keep the place after DoWriteDone.
  }

  bool IsFinish() { std::unique_lock lock(mu_); }

  bool Run(int cbState) override {
    if (!status_.ok()) {
      return false;
    } else {
      messages_waiting_--;
    }

    switch (cbState) {
      case State::STREAM_READY:
        cur_state_ = State::STREAM_READY;
        ToDoWrite();
        DoRead();
        break;
      case State::WRITE_DONE:
        msg_write_waiting_--;
        ToDoWrite();
        break;
      case State::READ_DONE:
        PostMsg();
        DoRead();
        break;
      case State::WRITE_DONE_FINISH: {
        is_finished_ = true;
        cur_state_ = State::WRITE_DONE_FINISH;
      } break;
      case State::FINISH_DONE:

        cur_state_ = State::FINISH_DONE;
        break;
      default:
        return false;
    }

    return true;
  }

  void StartNewClone() override {
    /*
    boost::asio::post(*io_, [&]() {
    AsyncRWStreamCall* clone =
    new AsyncRWStreamCall<R, W, FUNC>(GetPlayerId(), cb_, io_, req_);
    clone->StartInternal(100);
    });*/
  }

 private:
  void StartInternal(int messages_per_stream) {
    if (stream_ == nullptr) {
      return;
    }
    messages_per_stream_ = messages_per_stream;
    messages_issued_ = 0;
    cur_state_ = State::INITIALIZING;
    StreamMessageTag* msg =
        new StreamMessageTag(State::STREAM_READY, this->shared_from_this());
    stream_->StartCall(StreamMessageTag::Tag(msg));
    messages_waiting_++;

    // auto recv_status = new Status(grpc::StatusCode::UNKNOWN, "UNKNOWN");
    // 			auto func = new std::function<void()>([recv_status]() {
    // 				printf("-------dfadfdafdf");
    // 				if (recv_status->ok()) {
    // 					printf("Finish is ok!!!!!");

    // 				}
    // 			});

    StreamMessageTag* msg2 =
        new StreamMessageTag(State::FINISH_DONE, this->shared_from_this());
    stream_->Finish(&GetStatus(), msg2);
  }

  void ToDoWrite() {
    if (cur_state_ <= State::INITIALIZING ||
        cur_state_ >= State::WRITE_DONE_WAIT)
      return;

    int size = req_list_.size();
    if (size > 0) {
      std::map<int, std::shared_ptr<R>>::iterator iter = req_list_.begin();
      if (iter->second == nullptr) {
        DoWriteDone();
      } else {
        DoWrite(iter->second);
      }
      req_list_.erase(iter);
    }
  }

  void DoWrite(std::shared_ptr<R> req) {
    std::unique_lock<std::mutex> lock(mu_);
    if (cur_state_ >= State::WRITE_DONE_WAIT || is_finished_) return;
    if (messages_waiting_ >= MAX_WAITING_NUM ||
        cur_state_ == State::INITIALIZING) {
      req_list_.insert(std::make_pair(GetMsgId(), std::move(req)));
    } else {
      StreamMessageTag* msg =
          new StreamMessageTag(State::WRITE_DONE, this->shared_from_this());
      stream_->Write(*req, StreamMessageTag::Tag(msg));
      messages_waiting_++;
      msg_write_waiting_++;
    }
  }

  void DoWriteDone() {
    std::unique_lock<std::mutex> lock(mu_);
    if (messages_waiting_ >= MAX_WAITING_NUM || msg_write_waiting_ > 0 ||
        cur_state_ == State::INITIALIZING ||
        (!to_finish_ && req_list_.size() > 0)) {
      req_list_.insert(std::make_pair(GetMsgId(), nullptr));
    } else {
      cur_state_ = State::WRITE_DONE_WAIT;
      StreamMessageTag* msg = new StreamMessageTag(State::WRITE_DONE_FINISH,
                                                   this->shared_from_this());
      stream_->WritesDone(StreamMessageTag::Tag(msg));
      messages_waiting_++;
    }
  }

  void DoRead() {
    std::unique_lock<std::mutex> lock(mu_);
    if (cur_state_ != State::STREAM_READY || is_finished_) return;
    // reply_.Clear();
    StreamMessageTag* msg =
        new StreamMessageTag(State::READ_DONE, this->shared_from_this());
    stream_->Read(&reply_, StreamMessageTag::Tag(msg));
    messages_waiting_++;
  }

  void PostMsg() {
    auto self(shared_from_this());
    boost::asio::post(*io_, [this, self]() { (*cb_)(GetPlayerId(), &reply_); });
  }

 public:
  static const int MAX_WAITING_NUM = 8;
  stream_ptr stream_;
  int topic;
  std::map<int, std::shared_ptr<R>> req_list_;
  W reply_;
  /*  std::shared_ptr<R> req_;*/

 private:
  enum State {
    INVALID = 0,
    INITIALIZING,
    STREAM_READY,
    WRITE_DONE,
    READ_DONE,
    WRITE_DONE_WAIT,
    WRITE_DONE_FINISH,
    FINISH_DONE
  };

  std::mutex mu_;  //流结束锁
  State cur_state_;
  // RespCb cb_;
  std::shared_ptr<FUNC> cb_;
  std::shared_ptr<boost::asio::io_context> io_;
  bool to_finish_;    //即将结束
  bool is_finished_;  //已经结束

  // Allow a limit on number of messages in a stream
  int messages_per_stream_;
  int messages_issued_;
  int messages_waiting_;   //正在处理，等待返回的消息个数
  int msg_write_waiting_;  //正在等待写返回的消息个数
};
