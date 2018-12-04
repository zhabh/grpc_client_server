
#include <google/protobuf/message.h>
#include <grpcpp/grpcpp.h>
#include <boost/asio.hpp>

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::CompletionQueue;
using grpc::ServerCompletionQueue;
using grpc::Status;


template <class ServiceType>
class grpc_scene_mgr {
public:
	  
	grpc_scene_mgr() {
		
	}
	~grpc_scene_mgr() {
		server_->Shutdown();
		cq_->Shutdown();
		thread_.join();
		bool ok;
		void* got_tag;
		while (cq_->Next(&got_tag, &ok));
	}
	
	void Init(std::string& server_address) {
		
		ServerBuilder builder;

		builder.AddListeningPort(server_address,
                               grpc::InsecureServerCredentials());
    
		builder.RegisterService(&async_service_);
		cq_ = builder.AddCompletionQueue();
	    server_ = builder.BuildAndStart();

		thread_ = std::thread(&grpc_scene_mgr::ThreadFunc,this);
	}

	template <class RequestType, class ResponseType>
	void AddService(std::function<void(ServiceType*, ServerContext*, RequestType*,
                         ServerAsyncResponseWriter<ResponseType>*,
                         CompletionQueue*, ServerCompletionQueue*, void*)>
          request_unary_function,
		std::function<grpc::Status(RequestType*, ResponseType*)> process_rpc){

		auto request_unary = std::bind(
              request_unary_function, &async_service_, std::placeholders::_1,
              std::placeholders::_2, std::placeholders::_3, cq_.get(),
              cq_.get(), std::placeholders::_4);

		    
		auto process_rpc_bound =
			std::bind(process_rpc, std::placeholders::_1,
				std::placeholders::_2);

		new AsyncServerUnaryCall<RequestType,ResponseType>(request_unary, process_rpc_bound);
	}

	void ThreadFunc() {
		bool ok;
		void* got_tag;
		IAsyncServerCall* ctx;
		while(true) {
			if (!cq_->Next(&got_tag, &ok) || !ok) {
			  return;
			}
			if((ctx = DeTag(got_tag)) == nullptr){
				return;
			}
			if (!ctx->Run(ok)) {
				ctx->Reset();
			}
		}
	}


class IAsyncServerCall {
 public:
  IAsyncServerCall() {}
  virtual ~IAsyncServerCall() {};
  virtual void Start() {}
  virtual void Reset(){}
  virtual bool Run(bool ok) { return true; };
};
	
static void* Tag(IAsyncServerCall* c) { return static_cast<void*>(c); }
  
static IAsyncServerCall* DeTag(void* t) {
	if(t == nullptr) return nullptr;
	return static_cast<IAsyncServerCall*>(t);
}

/*
自删除的类，一旦接受到请求就新new一个对象来继续等待rpc，旧的对象在完成返回后自己delete
*/
template <class RequestType, class ResponseType>
class AsyncServerUnaryCall final : public IAsyncServerCall {
 public:
     typedef std::function<void(ServerContext*, RequestType*,
                           grpc::ServerAsyncResponseWriter<ResponseType>*,
                           void*)> REQ_FUNC;

	 typedef std::function<grpc::Status(RequestType*, ResponseType*)> INVOKE_FUNC;
  

	 AsyncServerUnaryCall(REQ_FUNC request_method, INVOKE_FUNC invoke_method)
		 : IAsyncServerCall(),
		 request_func_(request_method),
		 invoke_func_(invoke_method),
		 reply_(),
		 response_writer_(&srv_ctx_),
		 next_state_(State::READY) 
	 {
		 Start();
	 }

  virtual ~AsyncServerUnaryCall() override{ 
	  
  };

  void Start() override { 
	  next_state_ = State::INVOKE;
	  request_func_(&srv_ctx_, &req_, &response_writer_,
                      grpc_scene_mgr::Tag(this)); 
  }
      
  void Reset() override {
	
	  new AsyncServerUnaryCall(request_func_,invoke_func_);
	  next_state_ = State::FINISH;
	  Run(true);
	  /*srv_ctx_ = new ServerContext;
      req_ = RequestType();
      response_writer_ =
          new grpc::ServerAsyncResponseWriter<ResponseType>(srv_ctx_);

	  next_state_ = State::INVOKE;
      request_func_(srv_ctx_, &req_, response_writer_,
                      grpc_scene_mgr::Tag(this));*/
    }


  void DoInvoke() {
	  next_state_ = State::FINISH;
	  grpc::Status status = invoke_func_(&req_, &reply_);	//todo: timeout
	  std::cout << "DoInvoke finish!" << std::endl;
	  response_writer_.Finish(reply_, status, grpc_scene_mgr::Tag(this));
  }

  bool Run(bool ok) override {
    switch (next_state_) {
      case State::INVOKE:
		new AsyncServerUnaryCall(request_func_,invoke_func_);
		DoInvoke();
		return true;
	  case State::FINISH:
		  delete this;
		  return true;
      default:
        return false;
    }
  }

public:
	ServerAsyncResponseWriter<ResponseType> response_writer_;
	RequestType req_;
	ResponseType reply_;
private:
	ServerContext srv_ctx_;
	enum State { READY, INVOKE, FINISH };
	State next_state_;
	REQ_FUNC request_func_;
	INVOKE_FUNC invoke_func_;
};


private:
  std::thread thread_;
  std::unique_ptr<ServerCompletionQueue> cq_;
  ServiceType async_service_;
  std::unique_ptr<grpc::Server> server_;
  std::vector<std::unique_ptr<IAsyncServerCall>> contexts_;
};

