#include "framework.h"
#include "Logo.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "KeyManager.h"

HRESULT Logo::Initialize()
{
	// ����� �̹��� ����!

	//// �̱� �ؽ���
	//TextureManager::GetInstance()->InsertTexture(
	//	TextureManager::SINGLE,
	//	L"../Texture/Sana.jpg",
	//	L"Sana");


	return S_OK;
}

int Logo::Update()
{
	if (KeyManager::GetInstance()->KeyPressing('P')) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::MENU);
	}

	return NOEVENT;
}

void Logo::LateUpdate()
{
}

void Logo::Render()
{
	// ���!
	//TEXTINFO* pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Sana");

	//D3DXVECTOR3 centerVec = {
	//	pTextInfo->imageInfo.Width * 0.5f ,
	//	pTextInfo->imageInfo.Height * 0.5f ,
	//	0.f
	//};

	//GraphicDevice::GetInstance()->GetSprite()->Draw(
	//	pTextInfo->texture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)
	//);

}

void Logo::Release()
{
}
