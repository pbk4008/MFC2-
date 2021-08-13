#include "framework.h"
#include "Edit.h"
#include "KeyManager.h"
#include "TextureManager.h"

HRESULT Edit::Initialize()
{
	// 에디터 뭐 추가해야 하지
	TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Stage/Player/Attack/AKIHA_AKI01_000.png", L"Player");


	return S_OK;
}

int Edit::Update()
{


	return 0;
}

void Edit::LateUpdate()
{
}

void Edit::Render()
{
}

void Edit::Release()
{

}
