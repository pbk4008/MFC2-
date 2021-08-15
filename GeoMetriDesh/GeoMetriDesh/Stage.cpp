#include "framework.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "LineMgr.h"
#include "Player.h"
#include "SubObject.h"

HRESULT Stage::Initialize()
{
	// 플레이어 오브젝트
	objMgr = ObjectManager::GetInstance();
	objMgr->InsertObject<Player>(ObjectManager::PLAYER);
	objMgr->InsertObject<SubObject>(ObjectManager::TERRAIN);

	lineMgr = CLineMgr::GetInstance();
	lineMgr->LoadLine();
	return S_OK;
}

int Stage::Update()
{
	objMgr->Update();

	return NOEVENT;
}

void Stage::LateUpdate()
{
	objMgr->LateUpdate();
}

void Stage::Render()
{
	objMgr->Render();
	lineMgr->Render();
}

void Stage::Release()
{
	SAFE_DELETE(objMgr);
}
