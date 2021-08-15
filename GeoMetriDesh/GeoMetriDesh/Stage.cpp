#include "framework.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "Player.h"


#include "SubObject.h"

HRESULT Stage::Initialize()
{
	// �÷��̾� ������Ʈ
	objMgr = ObjectManager::GetInstance();
	objMgr->InsertObject<Player>(ObjectManager::PLAYER);
	objMgr->InsertObject<SubObject>(ObjectManager::TERRAIN);

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
}

void Stage::Release()
{
	SAFE_DELETE(objMgr);
}
