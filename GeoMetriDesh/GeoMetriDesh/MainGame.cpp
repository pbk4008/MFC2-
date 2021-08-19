#include "framework.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "SoundMgr.h"


MainGame::MainGame()
{
	graphicDevice = GraphicDevice::GetInstance();
	sceneManager = SceneManager::GetInstance();

}

MainGame::~MainGame()
{
	ReleaseMainGame();
}

HRESULT MainGame::ReadyMainGame()
{
	CSoundMgr::Get_Instance()->Initialize();

	// 메인 진입점
	// HDC 필요한지 모르겠지만 일단 넣어놨습니다.
	g_hDC = GetDC(g_hWnd);

	// 그래픽카드한테 일 시킬 준비
	graphicDevice->ReadyGraphicDevice();

	//HRESULT hh = TextureManager::GetInstance()->InsertTexture(
	//	TextureManager::SINGLE,
	//	L"../Texture/BackGround/Black.png",
	//	L"Black");

	//sceneManager->ChangeScene(SceneManager::MENU);
	sceneManager->ChangeScene(SceneManager::EDIT);


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
	CSoundMgr::Destroy_Instance();
	SceneManager::DestroyInstance();
	// 그래픽카드 장치 반납
	graphicDevice->DestroyInstance();
}

MainGame* MainGame::Create()
{
	// 싱글톤 패턴 아님 주의!!!!
	MainGame* mInstance = new MainGame;

	if (FAILED(mInstance->ReadyMainGame())) {
		SAFE_DELETE(mInstance);
	}

	return mInstance;
}
