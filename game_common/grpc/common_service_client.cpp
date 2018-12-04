#include "stdafx.h"

#include "common_service_client.h"

void ResponseThreadFunc(void* cq) {
  grpc::CompletionQueue* q = static_cast<CompletionQueue*>(cq);

  void* got_tag;

  bool ok = false;
  while (q->Next(&got_tag, &ok)) {
    auto pCall = StreamMessageTag::DeTag(got_tag);
    if (pCall) {
      LogMgr::GetInstance()->Warn(
          "{0} ::cb_state= {1} ok?={2} grpc_code={3} grpc_msg={4} "
          "grpc_details={5}",
          pCall->client_call_->name(), pCall->cb_state_, ok,
          pCall->client_call_->GetStatus().error_code(),
          pCall->client_call_->GetStatus().error_message(),
          pCall->client_call_->GetStatus().error_details());
      if (ok && !pCall->client_call_->Run(pCall->cb_state_)) {
      }
      delete pCall;
      pCall = nullptr;
    }
  }
}

CommonServiceClient* CommonServiceClient::instance_ = nullptr;

CommonServiceClient::CommonServiceClient() {
  scene_mgr_ip_[0] = '\0';
  scene_area_ip_[0] = '\0';
  player_session_ip_[0] = '\0';
  inited_ = false;
}

CommonServiceClient::~CommonServiceClient() { Destory(); }

bool CommonServiceClient::Init() {
  if (inited_) {
    return false;
  }

  LoadServiceSettings();

  std::string address_scene_area(scene_area_ip_);
  std::shared_ptr<Channel> channel_scene_area = grpc::CreateChannel(
      address_scene_area, grpc::InsecureChannelCredentials());
  stub_scene_area_ = scenearea::SceneAreaService::NewStub(channel_scene_area);

  std::string address_scene_mgr(scene_mgr_ip_);
  std::shared_ptr<Channel> channel_scene_mgr = grpc::CreateChannel(
      address_scene_mgr, grpc::InsecureChannelCredentials());
  stub_scene_mgr_ = SceneManagerService::NewStub(channel_scene_mgr);

  response_thread_ = std::thread(ResponseThreadFunc, &cq_);
  context_ = GetIoService();

  inited_ = true;
  return true;
}

void CommonServiceClient::LoadServiceSettings() {
  IIniFile* piIniFile = nullptr;

  piIniFile = g_OpenIniFile("config.ini");

  // logic server
  piIniFile->GetString("SceneServiceServer", "Scene_Mgr_Address",
                       "127.0.0.1:54051", scene_mgr_ip_, 64);
  piIniFile->GetString("SceneServiceServer", "Scene_Area_Address",
                       "127.0.0.1:9001", scene_area_ip_, 64);
  piIniFile->GetString("SceneServiceServer", "Player_Session_Address",
                       "127.0.0.1:55051", player_session_ip_, 64);
}

void CommonServiceClient::IdToString(char* buf, uint64_t id) {
  sprintf(buf, "%llu", id);
}

void CommonServiceClient::DoEnterSceneRequest(uint64 roleId, uint32 mapId,
                                              int copyId, int lineId,
                                              int createTag) {
  auto response = std::make_shared<AsyncClientUnaryCall<EnterSceneResponse>>(
      roleId,
      std::bind(&CommonServiceClient::OnEnterSceneResponse, this,
                std::placeholders::_1, std::placeholders::_2),
      context_);

  EnterSceneRequest req;
  req.set_player_session(roleId);
  req.set_ip_address("192.168.1.109");
  req.set_port(55051);
  req.set_map_id(mapId);
  req.set_map_copy_idx(copyId);

  std::shared_ptr<ClientAsyncResponseReader<EnterSceneResponse>> creat_reader_(
      std::move(stub_scene_mgr_->AsyncEnterScene(&response->GetContext(), req,
                                                 &cq_)));

  response->set_reader(creat_reader_);

  response->Start();
}

void CommonServiceClient::OnEnterSceneResponse(uint64,
                                               google::protobuf::Message* msg) {
  std::cout << "Receive message OnEnterSceneResponse!" << std::endl;
  EnterSceneResponse* rep = (EnterSceneResponse*)msg;
  LogMgr::GetInstance()->Log("Receive message OnEnterSceneResponse!\n");
}

void CommonServiceClient::DoEnterAreaSceneRequest(uint64 roleId,
                                                  std::string ipAddress,
                                                  uint32 port, uint32 mapId,
                                                  int copyId) {
  auto response =
      std::make_shared<AsyncClientUnaryCall<scenearea::EnterSceneResponse>>(
          roleId,
          std::bind(&CommonServiceClient::OnEnterAreaSceneResponse, this,
                    std::placeholders::_1, std::placeholders::_2),
          context_);

  scenearea::EnterSceneRequest req;
  req.set_player_session(roleId);
  req.set_ip_address(ipAddress);
  req.set_port(port);
  req.set_map_id(mapId);
  req.set_map_copy_idx(copyId);
  req.set_result_code(0);
  req.set_target_server_idx(0);
  req.set_line_id(0);

  std::shared_ptr<ClientAsyncResponseReader<scenearea::EnterSceneResponse>>
      creat_reader_(std::move(stub_scene_area_->AsyncEnterScene(
          &response->GetContext(), req, &cq_)));

  response->set_reader(creat_reader_);

  response->Start();
}

void CommonServiceClient::OnEnterAreaSceneResponse(
    uint64, google::protobuf::Message* msg) {
  scenearea::EnterSceneResponse* rep = (scenearea::EnterSceneResponse*)msg;
  LogMgr::GetInstance()->Log("Receive message OnEnterAreaSceneResponse!\n");
}
