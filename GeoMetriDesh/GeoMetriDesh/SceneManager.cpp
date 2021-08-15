#include "framework.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Logo.h"
#include "Menu.h"
#include "Edit.h"
#include "Stage.h"


IMPLEMENT_SINGLETON(SceneManager)
void SceneManager::ChangeScene(SCENE_ID _ID)
{
	currScene = _ID;


	if (preScene != currScene) 
	{
		Release();

		switch (_ID)
		{
		case SceneManager::LOGO:
			scene = new Logo;
			break;
		case SceneManager::MENU:
			scene = new Menu;
			break;
		case SceneManager::EDIT:
			scene = new CEdit;
			break;
		case SceneManager::STAGE:
			scene = new Stage;
			break;
		}

		scene->Initialize();
		preScene = currScene;
	}
}

void SceneManager::Update()
{
	scene->Update();
}

void SceneManager::LateUpdate()
{
	scene->LateUpdate();
}

void SceneManager::Render()
{
	scene->Render();
}

void SceneManager::Release()
{
	SAFE_DELETE(scene);
}
