#pragma once

#include "Protocol/Relay_GS_Protocol.h"
#include <google/protobuf/message.h>
#include <grpcpp/grpcpp.h>
#include "boost/asio.hpp"
#include "scene_area_service.grpc.pb.h"
#include "player_manager_service.grpc.pb.h"
#include "client.h"

using boost::asio::io_context;
using grpc::Channel;
using grpc::CompletionQueue;

class KRole;
class KMapInfo;
class KMapCopy;
class KMapLineInfo;
class KGameCenterBase;


class session_client {
private:
	  static session_client* instance_;

	public:
		session_client() {
		}

		~session_client(){
			response_thread_.join();
			if (instance_ != nullptr) {
				delete instance_;
				instance_ = nullptr;
			}
		}

		  
		static session_client* GetInst() {
			if (instance_ == nullptr) {
				instance_ = new session_client();
			}
			return instance_;
		}

		bool Init(){
			std::shared_ptr<Channel> channel_ =
				grpc::CreateChannel(PlayerSessionAddr(), grpc::InsecureChannelCredentials());

			stub_player_ = playermanager::PlayerManagerService::NewStub(channel_);

			response_thread_ = std::thread(&session_client::SessionThreadFunc, this, &cq_);
			context_ = GetIoService();
			return true;
		}

		const char* PlayerSessionAddr(){
			return "127.0.0.1:55051";
		}

		void SessionThreadFunc(void* cq) {
			grpc::CompletionQueue* q = static_cast<CompletionQueue*>(cq);

			void* got_tag;

			bool ok = false;
			while (q->Next(&got_tag, &ok)) {
				auto pCall = StreamMessageTag::DeTag(got_tag);
				if (pCall) {
					if (ok && !pCall->client_call_->Run(pCall->cb_state_)) {
					}
					delete pCall;
					pCall = nullptr;
				}
		}
}
		void NoticeSwitchMap(uint32 map_id,int32 map_copy_idx,int32 line_id, int32 x,int32 y,int32 z,uint64 session_id) {
			auto response = std::make_shared<AsyncClientUnaryCall<playermanager::NoticeSwitchMapResponse>>(
				12,
				std::bind(&session_client::SwitchMapRespone, this,
					std::placeholders::_1, std::placeholders::_2),
				context_);

			playermanager::NoticeSwitchMapRequest req;
			req.set_map_id(map_id);
			req.set_copy_id(map_copy_idx);
			req.set_line_id(line_id);
			req.set_pos_x(x);
			req.set_pos_x(y);
			req.set_pos_x(z);
			req.set_session_id(session_id);
			std::shared_ptr<ClientAsyncResponseReader<playermanager::NoticeSwitchMapResponse>>
				creat_reader_(std::move(stub_player_->AsyncNoticeSwitchMap(
					&response->GetContext(), req, &cq_)));

			response->set_reader(creat_reader_);

			response->Start();
		}

		void SwitchMapRespone(uint64 uid, google::protobuf::Message* msg) {
			playermanager::NoticeSwitchMapResponse* rep = (playermanager::NoticeSwitchMapResponse*)msg;

		}



	public:
		grpc::CompletionQueue cq_;
		std::thread response_thread_;
		std::shared_ptr<io_context> context_;
		std::unique_ptr<playermanager::PlayerManagerService::Stub> stub_player_;
};
