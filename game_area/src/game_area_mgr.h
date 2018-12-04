#pragma once
#include "Common/KG_Socket.h"
#include "Protocol/Relay_GS_Protocol.h"
#include "scene_area_service.grpc.pb.h"
#include <list>
#include <grpc_server_call.h>


class KPlayer;
class KScene;
struct KHeroData;
class KPB_SAVE_DATA;

class game_area_mgr
{
public:
    game_area_mgr();
	~game_area_mgr();
	BOOL Init(std::string& server_address);
	void RegisterServer();
	virtual void UnInit(){}
	virtual void Activate(){}
	virtual void Quit(){}
	grpc::Status EnterScene(scenearea::EnterSceneRequest* req,scenearea::EnterSceneResponse* res);

private:
	bool CreateMap(uint32 map_id,int32 copy_id);

public:
	std::unique_ptr<grpc_server_call<scenearea::SceneAreaService::AsyncService>> scene_mgr_;
};

