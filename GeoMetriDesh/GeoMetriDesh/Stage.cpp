#include "framework.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "LineMgr.h"
#include "Player.h"
#include "SubObject.h"
#include "Land.h"

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

	TextureManager::GetInstance()->InsertTexture(
		TextureManager::MULTI, 
		L"../Texture/Obstacle/Obstacle00%d.png", 
		L"Tile", 
		L"Obstacle", 6);

	// RGB값 조정 가능
	rgb.A = 150;
	rgb.R = 0;
	rgb.G = 0;
	rgb.B = 255;

	eColor = BLUE;
	dwCurTime = GetTickCount64();//색깔 체인지 시간
	// 플레이어 오브젝트
	objMgr = ObjectManager::GetInstance();
	objMgr->InsertObject<Player>(ObjectManager::PLAYER);
	//objMgr->InsertObject<SubObject>(ObjectManager::TERRAIN);

	lineMgr = CLineMgr::GetInstance();
	lineMgr->LoadLine();

	objMgr->InsertObject<CLand>(ObjectManager::TERRAIN);
	
	return S_OK;
}

int Stage::Update()
{
	objMgr->Update();
	ChangeColor();
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
	//lineMgr->Render();
}

void Stage::Release()
{
	SAFE_DELETE(objMgr);
}

void Stage::ChangeColor()
{
	if (dwCurTime + 10000 < GetTickCount64())
	{
		eColor = COLOR(eColor + 1);
		if (eColor == END)
			eColor = BLUE;
		dwCurTime = GetTickCount64();
	}
	switch (eColor)
	{
	case BLUE:
		rgb.R += 1.0f;
		if (rgb.R >= 255)
			rgb.R = 255;
		break;
	case PURPLE:
		rgb.B -= 1.f;
		if (rgb.B <= 0)
			rgb.B = 0;
		break;
	case RED:
		rgb.B += 1.f;
		if (rgb.B >= 255)
			rgb.B = 255;
		break;
	case REPURPLE:
		rgb.R -= 1.f;
		if (rgb.R <= 0)
			rgb.R = 0;
		break;
	}
	dynamic_cast<CLand*>(objMgr->GetList(ObjectManager::TERRAIN).back())->setColor(rgb);
}
