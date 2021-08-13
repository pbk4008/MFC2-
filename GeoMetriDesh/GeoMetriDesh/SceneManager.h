#pragma once
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

class Scene;
class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
public:
	enum SCENE_ID {LOGO, MENU, STATE, END};
private:
	inline explicit SceneManager() {};
public:
	inline virtual ~SceneManager() {};


	void ChangeScene();
	void Update();
	void LateUpdate();
	void Render();
	void Release();


private:
	Scene* scene;
	SCENE_ID currScene;
	SCENE_ID preSCENE;
};


#endif // !__SCENE_MANAGER_H__