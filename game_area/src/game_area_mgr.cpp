#include "stdafx.h"
#include "Protocol/Relay_GS_Protocol.h"
#include "game_area_mgr.h"
#include "KRelayClient.h"
#include "Engine/KG_CreateGUID.h"
#include "Engine/KG_Time.h"
#include "KRoleDBDataDef.h"
#include "KPlayer.h"
#include "KGameWorld.h"
#include "KPlayerServer.h"
#include "KScene.h"
#include "KLSClient.h"
#include "GatewayDef.h"
#include "Protocol/cl2gw_protocol.h"
#include "Protocol/gw2cl_protocol.h"
#include "KGWClient.h"
#include "KSceneGround.h"
#include "KSceneSpace.h"


game_area_mgr::game_area_mgr():
	scene_mgr_(new grpc_server_call<scenearea::SceneAreaService::AsyncService>()){

}

game_area_mgr::~game_area_mgr(){
	
}

BOOL game_area_mgr::Init(std::string& server_address){
	scene_mgr_->Init(server_address);
	return true;
}

void game_area_mgr::RegisterServer(){
		
	auto func = std::bind(&game_area_mgr::EnterScene, this, std::placeholders::_1,
				std::placeholders::_2);

	scene_mgr_->AddService<scenearea::EnterSceneRequest,scenearea::EnterSceneResponse>(
		&scenearea::SceneAreaService::AsyncService::RequestEnterScene,
		func
		);

}

grpc::Status game_area_mgr::EnterScene(scenearea::EnterSceneRequest* pReq,scenearea::EnterSceneResponse* res)
{
	bool                        bRetCode            = false;
   
	bRetCode = true;

Exit0:
	//res->set_result(scenearea::ResultCode::SUCCESS);
    return grpc::Status::OK;
}

	
bool game_area_mgr::CreateMap(uint32 map_id,int32 copy_id){
	
	BOOL                    bResult                 = false;
    BOOL                    bRetCode                = false;
    KScene*                 pScene                  = NULL;
    BOOL                    bSceneInitFlag          = false;
	int						map_type				= -1;

	

    bResult = true;
Exit0:
	if (bResult)
	{
		//地图创建成功.
	}
	else
    {
		//地图创建不成功.

    }
    return bResult;
}
