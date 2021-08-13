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
	// ���� ������

	// HDC �ʿ����� �𸣰����� �ϴ� �־�����ϴ�.
	g_hDC = GetDC(g_hWnd);

	// �׷���ī������ �� ��ų �غ�
	graphicDevice->ReadyGraphicDevice();

	// ���Ŵ���!
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
	// ��� ������ ����
	graphicDevice->GetInstance()->RenderBegin();

	sceneManager->Render();

	// ��� ������ ��
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
	// �׷���ī�� ��ġ �ݳ�
{
	// �̱��� ���� �ƴ� ����!!!!
	MainGame* mInstance = new MainGame;

	if (FAILED(mInstance->ReadyMainGame())) {
		SAFE_DELETE(mInstance);
	}

	return mInstance;
}
