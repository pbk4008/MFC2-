#pragma once
#ifndef __LOGO_H__
#define __LOGO_H___

#include "Scene.h"
class Logo : public Scene
{
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

};



#endif // !__LOGO_H__