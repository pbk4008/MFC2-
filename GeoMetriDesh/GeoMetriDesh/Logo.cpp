#include "framework.h"
#include "Logo.h"
#include "TextureManager.h"
HRESULT Logo::Initialize()
{
	// 출력할 이미지 저장!

	// 싱글 텍스쳐
	TextureManager::GetInstance()->InsertTexture(
		TextureManager::SINGLE,
		L"../Texture/Sana.png",
		L"Logo");


	return S_OK;
}

int Logo::Update()
{
	return 0;
}

void Logo::LateUpdate()
{
}

void Logo::Render()
{
	// 출력!
	TEXTINFO* pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Logo");

	D3DXVECTOR3 centerVec = {
		float(pTextInfo->imageInfo.Width >> 1),
		float(pTextInfo->imageInfo.Height >> 1),
		0.f
	};

	GraphicDevice::GetInstance()->GetSprite()->Draw(
		pTextInfo->texture, nullptr, &centerVec, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)
	);

}

void Logo::Release()
{
}
