#include "framework.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "LineMgr.h"
#include "Player.h"
#include "SubObject.h"

HRESULT Stage::Initialize()
{
	// 배경!
	TextureManager::GetInstance()->InsertTexture(
		TextureManager::SINGLE,
		L"../Texture/BackGround/Square.png",
		L"BackGround");

	TextureManager::GetInstance()->InsertTexture(
		TextureManager::SINGLE,
		L"../Texture/BackGround/Square1.png",
		L"BackGround1");

	// RGB값 조정 가능
	rgb.A = 150;
	rgb.R = 0;
	rgb.G = 255;
	rgb.B = 0;

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
	TEXTINFO* pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"BackGround");

	D3DXVECTOR3 centerVec = {
		float(pTextInfo->imageInfo.Width >> 1),
		float(pTextInfo->imageInfo.Height >> 1),
		0.f
	};

	GraphicDevice::GetInstance()->GetSprite()->Draw(
		pTextInfo->texture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
	);
	// 배경 끝나고

	objMgr->Render();
	lineMgr->Render();
}

void Stage::Release()
{
	SAFE_DELETE(objMgr);
}
