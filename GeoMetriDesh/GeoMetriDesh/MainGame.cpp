#include "framework.h"
#include "MainGame.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "KeyManager.h"

MainGame::MainGame()
{
	graphicDevice = GraphicDevice::GetInstance();
	ObjectManager::GetInstance();
	SceneManager::GetInstance();
	KeyManager::GetInstance();
}

MainGame::~MainGame()
{
	ReleaseMainGame();
}

HRESULT MainGame::ReadyMainGame()
{
	// 메인 진입점

	// HDC 필요한지 모르겠지만 일단 넣어놨습니다.
	g_hDC = GetDC(g_hWnd);

	// 그래픽카드한테 일 시킬 준비
	graphicDevice->ReadyGraphicDevice();

	// 씬매니저!
	sceneManager = SceneManager::GetInstance();
	sceneManager->ChangeScene(SceneManager::LOGO);

	return S_OK;
}

void MainGame::UpdateMainGame()
{
	sceneManager->Update();
}

void MainGame::LateUpdateMainGame()
{
	sceneManager->LateUpdate();
}

void MainGame::RenderMainGame()
{
	// 모든 랜더의 시작
	graphicDevice->GetInstance()->RenderBegin();

	sceneManager->Render();

	// 모든 랜더의 끝
	graphicDevice->GetInstance()->RenderEnd();
}

void MainGame::ReleaseMainGame()
{
	ObjectManager::DestroyInstance();
	SceneManager::DestroyInstance();
	KeyManager::DestroyInstance();

	graphicDevice->DestroyInstance();
}

MainGame* MainGame::Create()
	// 그래픽카드 장치 반납
{
	// 싱글톤 패턴 아님 주의!!!!
	MainGame* mInstance = new MainGame;

	if (FAILED(mInstance->ReadyMainGame())) {
		SAFE_DELETE(mInstance);
	}

	return mInstance;
}
