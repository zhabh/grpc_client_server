// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: scene_area_service.proto
#ifndef GRPC_scene_5farea_5fservice_2eproto__INCLUDED
#define GRPC_scene_5farea_5fservice_2eproto__INCLUDED

#include "scene_area_service.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace scenearea {

// //////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// //////////////////////////////////////////////////////////////////////////////////////////////////////////
class SceneAreaService final {
 public:
  static constexpr char const* service_full_name() {
    return "scenearea.SceneAreaService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // what: 订阅消息，可订阅SubscribeTopic中的定义的数据信息变化，在该类数据变化时主动通知所有的订阅者
    // when: 可在游戏启动时进行相关订阅，也可以在游戏过程中按需要进行订阅
    virtual ::grpc::Status EnterScene(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::scenearea::EnterSceneResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::scenearea::EnterSceneResponse>> AsyncEnterScene(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::scenearea::EnterSceneResponse>>(AsyncEnterSceneRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::scenearea::EnterSceneResponse>> PrepareAsyncEnterScene(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::scenearea::EnterSceneResponse>>(PrepareAsyncEnterSceneRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::scenearea::EnterSceneResponse>* AsyncEnterSceneRaw(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::scenearea::EnterSceneResponse>* PrepareAsyncEnterSceneRaw(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status EnterScene(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::scenearea::EnterSceneResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::scenearea::EnterSceneResponse>> AsyncEnterScene(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::scenearea::EnterSceneResponse>>(AsyncEnterSceneRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::scenearea::EnterSceneResponse>> PrepareAsyncEnterScene(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::scenearea::EnterSceneResponse>>(PrepareAsyncEnterSceneRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::scenearea::EnterSceneResponse>* AsyncEnterSceneRaw(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::scenearea::EnterSceneResponse>* PrepareAsyncEnterSceneRaw(::grpc::ClientContext* context, const ::scenearea::EnterSceneRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_EnterScene_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // what: 订阅消息，可订阅SubscribeTopic中的定义的数据信息变化，在该类数据变化时主动通知所有的订阅者
    // when: 可在游戏启动时进行相关订阅，也可以在游戏过程中按需要进行订阅
    virtual ::grpc::Status EnterScene(::grpc::ServerContext* context, const ::scenearea::EnterSceneRequest* request, ::scenearea::EnterSceneResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_EnterScene : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_EnterScene() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_EnterScene() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status EnterScene(::grpc::ServerContext* context, const ::scenearea::EnterSceneRequest* request, ::scenearea::EnterSceneResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestEnterScene(::grpc::ServerContext* context, ::scenearea::EnterSceneRequest* request, ::grpc::ServerAsyncResponseWriter< ::scenearea::EnterSceneResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_EnterScene<Service > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_EnterScene : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_EnterScene() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_EnterScene() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status EnterScene(::grpc::ServerContext* context, const ::scenearea::EnterSceneRequest* request, ::scenearea::EnterSceneResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_EnterScene : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_EnterScene() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::scenearea::EnterSceneRequest, ::scenearea::EnterSceneResponse>(std::bind(&WithStreamedUnaryMethod_EnterScene<BaseClass>::StreamedEnterScene, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_EnterScene() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status EnterScene(::grpc::ServerContext* context, const ::scenearea::EnterSceneRequest* request, ::scenearea::EnterSceneResponse* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedEnterScene(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::scenearea::EnterSceneRequest,::scenearea::EnterSceneResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_EnterScene<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_EnterScene<Service > StreamedService;
};

}  // namespace scenearea


#endif  // GRPC_scene_5farea_5fservice_2eproto__INCLUDED