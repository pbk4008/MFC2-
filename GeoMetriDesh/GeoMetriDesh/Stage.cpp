#include "framework.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "Player.h"
#include "SubObject.h"
#include "Land.h"
#include "RunEffect.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

HRESULT Stage::Initialize()
{
	// 배경!
	TextureManager::GetInstance()->InsertTexture(
		TextureManager::SINGLE,
		L"../Texture/BackGround/RectangleLarge.png",
		L"RectangleLarge1");

	TextureManager::GetInstance()->InsertTexture(
		TextureManager::SINGLE,
		L"../Texture/BackGround/RectangleLarge2.png",
		L"RectangleLarge2");

	TextureManager::GetInstance()->InsertTexture(TextureManager::MULTI, L"../Texture/Obstacle/Obstacle00%d.png", L"Tile", L"Obstacle", 19);

	// RGB값 조정 가능
	rgb.A = 150;
	rgb.R = 0;
	rgb.G = 0;
	rgb.B = 255;

	eColor = BLUE;
	dwCurTime = GetTickCount64();//색깔 체인지 시간
	// 플레이어 오브젝트
	objMgr = ObjectManager::GetInstance();
	

	//objMgr->InsertObject<SubObject>(ObjectManager::TERRAIN);

	lineMgr = CLineMgr::GetInstance();
	lineMgr->LoadLine();

	objMgr->InsertObject<CLand>(ObjectManager::TERRAIN);
	objMgr->InsertObject<Player>(ObjectManager::PLAYER);
	CScrollMgr::GetInstance()->setSpeed(3.f);


	CScrollMgr::GetInstance()->reSetSpeed();
	CScrollMgr::GetInstance()->setSpeed(3.f);

	CScrollMgr::GetInstance()->reSetBackSpeed();
	CScrollMgr::GetInstance()->setBackSpeed(2.f);
	
	CSoundMgr::Get_Instance()->PlayBGM(L"01.Forever Bound - Stereo Madness.mp3");
	dwSpawnTime = GetTickCount64();
	return S_OK;
}

int Stage::Update()
{
	CScrollMgr::GetInstance()->XUpdate();
	if (dwSpawnTime + 10 <= GetTickCount64())
	{
		objMgr->LoadObject();
		dwSpawnTime = GetTickCount64();
	}
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
	D3DXMATRIX matScale, matTrans,matWorld;
	D3DXMatrixIdentity(&matWorld);
	GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	float scollX = CScrollMgr::GetInstance()->getBackGroundScrollX();

	TEXTINFO* pTextInfo1 = TextureManager::GetInstance()->GetTextInfo(L"RectangleLarge1");
	D3DXVECTOR3 centerVec1 = {
	   +scollX,
		0.f,
		0.f
	};

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, WINCX, 0.f, 0.f);
	matScale *= matTrans;
	GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matScale);

	GraphicDevice::GetInstance()->GetSprite()->Draw(
		pTextInfo1->texture, nullptr, &centerVec1, nullptr, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
	);

	TEXTINFO* pTextInfo2 = TextureManager::GetInstance()->GetTextInfo(L"RectangleLarge2");
	D3DXVECTOR3 centerVec2 = {
	   pTextInfo1->imageInfo.Width + (+scollX),
		0.f,
		0.f
	};

	GraphicDevice::GetInstance()->GetSprite()->Draw(
		pTextInfo2->texture, nullptr, &centerVec2, nullptr, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
	);
	// 배경 끝나고
	if (scollX >= pTextInfo1->imageInfo.Width) {
		CScrollMgr::GetInstance()->setBackGroundScrollX(0.f);
	}
	objMgr->Render();
	lineMgr->Render();
}

void Stage::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
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
	dynamic_cast<CLand*>(objMgr->GetList(ObjectManager::TERRAIN).front())->setColor(rgb);
}
