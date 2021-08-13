#pragma once
#ifndef __EDIT_H__
#define __EDIT_H__

#include "Scene.h"
class Edit : public Scene
{
private:
	inline explicit Edit() {};
public:
	inline virtual ~Edit() { Release(); };

	// Scene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

#endif // !__EDIT_H__