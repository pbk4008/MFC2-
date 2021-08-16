#pragma once
#ifndef __MENU_H__
#define __MENU_H__

#include "Scene.h"
class ObjectManager;
class KeyManager;
class Menu : public Scene
{
public:
	Menu() {};
	~Menu() { Release(); };

	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetPlayBtn();
	void KeyChecking();

private:
	bool btnCollisionCheck;

	int subScroll;
};


#endif // !__MENU_H__