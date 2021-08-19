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

	// ���� ������
	// HDC �ʿ����� �𸣰����� �ϴ� �־�����ϴ�.
	g_hDC = GetDC(g_hWnd);

	// �׷���ī������ �� ��ų �غ�
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
	// ��� ������ ����
	graphicDevice->GetInstance()->RenderBegin();

	sceneManager->Render();

	// ��� ������ ��
	graphicDevice->GetInstance()->RenderEnd();
}

void MainGame::ReleaseMainGame()
{
	CSoundMgr::Destroy_Instance();
	SceneManager::DestroyInstance();
	// �׷���ī�� ��ġ �ݳ�
	graphicDevice->DestroyInstance();
}

MainGame* MainGame::Create()
{
	// �̱��� ���� �ƴ� ����!!!!
	MainGame* mInstance = new MainGame;

	if (FAILED(mInstance->ReadyMainGame())) {
		SAFE_DELETE(mInstance);
	}

	return mInstance;
}
