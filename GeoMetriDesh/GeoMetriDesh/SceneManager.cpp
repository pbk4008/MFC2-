#include "framework.h"
#include "SceneManager.h"
#include "Logo.h"
#include "Menu.h"
//#include "Edit.h"


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
			//scene = new Edit;
			break;
		case SceneManager::STAGE:
			// scene = new State;
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
