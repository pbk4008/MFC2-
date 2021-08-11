#include "framework.h"
#include "MainGame.h"
#include "TextureManager.h"

MainGame::MainGame()
{
	graphicDevice = GraphicDevice::GetInstance();
}

MainGame::~MainGame()
{
	ReleaseMainGame();
}

HRESULT MainGame::ReadyMainGame()
{
	g_hDC = GetDC(g_hWnd);
	graphicDevice->ReadyGraphicDevice();

	return S_OK;
}

void MainGame::UpdateMainGame()
{
}

void MainGame::LateUpdateMainGame()
{
}

void MainGame::RenderMainGame()
{
	graphicDevice->GetDevice()->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1, 0);
	graphicDevice->GetDevice()->BeginScene();
	// 아직 스프라이트 모름
	graphicDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEXTINFO* pTexInfo = TextureManager::GetInstance()->GetTextInfo(L"Logo");


	//아직 스프라이트 없음
	graphicDevice->GetSprite()->End();
	graphicDevice->GetDevice()->EndScene();
	graphicDevice->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}

void MainGame::ReleaseMainGame()
{
	graphicDevice->DestroyInstance();
}

MainGame* MainGame::Create()
{
	MainGame* mInstance = new MainGame;

	if (FAILED(mInstance->ReadyMainGame())) {
		SAFE_DELETE(mInstance);
	}

	return mInstance;
}
