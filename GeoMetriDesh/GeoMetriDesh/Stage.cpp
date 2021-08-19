#include "framework.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "LineMgr.h"
#include "Player.h"
#include "SubObject.h"
#include "Land.h"
#include "RunEffect.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

HRESULT Stage::Initialize()
{
	// ���!
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

	// RGB�� ���� ����
	rgb.A = 150;
	rgb.R = 0;
	rgb.G = 0;
	rgb.B = 255;

	eColor = BLUE;
	dwCurTime = GetTickCount64();//���� ü���� �ð�
	// �÷��̾� ������Ʈ
	objMgr = ObjectManager::GetInstance();
	objMgr->InsertObject<Player>(ObjectManager::PLAYER);
	

	//objMgr->InsertObject<SubObject>(ObjectManager::TERRAIN);

	lineMgr = CLineMgr::GetInstance();
	lineMgr->LoadLine();

	objMgr->InsertObject<CLand>(ObjectManager::TERRAIN);



	CScrollMgr::GetInstance()->reSetSpeed();
	CScrollMgr::GetInstance()->setSpeed(2.f);
	
	CSoundMgr::Get_Instance()->PlayBGM(L"01.Forever Bound - Stereo Madness.mp3");

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
	D3DXMATRIX matWorld, matScale, matTrans;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f);

	TEXTINFO* pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"BackGround");
	D3DXVECTOR3 centerVec = {
		float(pTextInfo->imageInfo.Width >> 1),
		float(pTextInfo->imageInfo.Height >> 1),
		0.f
	};

	matWorld = matScale * matTrans;
	GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	GraphicDevice::GetInstance()->GetSprite()->Draw(
		pTextInfo->texture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
	);
	// ��� ������

	objMgr->Render();
	//lineMgr->Render();
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
