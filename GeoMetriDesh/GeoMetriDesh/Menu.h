#pragma once
#ifndef __MENU_H__
#define __MENU_H__

#include "Scene.h"
class Menu : public Scene
{
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};


#endif // !__MENU_H__