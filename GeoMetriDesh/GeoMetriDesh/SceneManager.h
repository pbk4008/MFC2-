#pragma once
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

class Scene;
class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
public:
	enum SCENE_ID {LOGO, MENU, EDIT, STAGE, SCENE_ID_END};
private:
	inline explicit SceneManager() : scene(nullptr), currScene(LOGO), preScene(SCENE_ID_END){};
public:
	inline virtual ~SceneManager() {};


	void ChangeScene(SCENE_ID _ID);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void FadeIn();
	void FadeOut();


private:
	Scene* scene;
	SCENE_ID currScene;
	SCENE_ID preScene;

	DWORD dwFadeTime;

	int aa = 255;
	bool fadeChcck = false;
};


#endif // !__SCENE_MANAGER_H__