#include "framework.h"
#include "MainGame.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "Player.h"

MainGame::MainGame()
{
	graphicDevice = GraphicDevice::GetInstance();
	objectManager = ObjectManager::GetInstance();
}

MainGame::~MainGame()
{
	ReleaseMainGame();
}

HRESULT MainGame::ReadyMainGame()
{
	g_hDC = GetDC(g_hWnd);
	graphicDevice->ReadyGraphicDevice();
	objectManager->Intialize();
	


	objectManager->InsertObject<Player>(ObjectManager::PLAYER);

	return S_OK;
}

void MainGame::UpdateMainGame()
{
	objectManager->Update();
}

void MainGame::LateUpdateMainGame()
{
	objectManager->LateUpdate();
}

void MainGame::RenderMainGame()
{
	graphicDevice->GetInstance()->RenderBegin();

	objectManager->Render();

	graphicDevice->GetInstance()->RenderEnd();
}

void MainGame::ReleaseMainGame()
{
	objectManager->Release();

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
