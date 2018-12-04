#pragma once

#include <google/protobuf/message.h>
#include <grpcpp/grpcpp.h>
#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include "grpc_client.h"
#include "scene_area_service.grpc.pb.h"

using boost::asio::io_context;
using grpc::Channel;
using grpc::CompletionQueue;


class CommonServiceClient {
 public:
  CommonServiceClient();
  ~CommonServiceClient();


  static CommonServiceClient* GetInst() {
    if (instance_ == nullptr) {
      instance_ = new CommonServiceClient();
    }

    return instance_;
  }

  void Destory() {
    if (instance_ != nullptr) {
      delete instance_;
      instance_ = nullptr;
    }
    response_thread_.detach();
  }

  bool Init();

  void LoadServiceSettings();

  void IdToString(char* buf, uint64_t id);

  std::shared_ptr<io_context>& GetContext(){ return context_; }

 public:
  //-------------场景管理暂时-----------------------------
  void DoEnterSceneRequest(uint64 playerId, uint32 mapId, int copyId, int lineId, int createTag);

  void DoEnterAreaSceneRequest(uint64 roleId, std::string ipAddress, uint32 port, uint32 mapId, int copyId);

public:  //Response handle function
  void OnEnterSceneResponse(uint64, google::protobuf::Message* msg);

  void OnEnterAreaSceneResponse(uint64, google::protobuf::Message* msg);

 public:
  std::thread response_thread_;

  char scene_mgr_ip_[64];
  char scene_area_ip_[64];
  char player_session_ip_[64];

 private:
  static CommonServiceClient* instance_;
  grpc::CompletionQueue cq_;
  std::shared_ptr<io_context> context_;
  std::unique_ptr<scenearea::SceneAreaService::Stub> stub_scene_area_;
  std::unique_ptr<scenemanager::SceneManagerService::Stub> stub_scene_mgr_;

  bool inited_;
};
