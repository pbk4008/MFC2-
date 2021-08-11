#pragma once
#include "Object.h"
#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player : public Object
{
public:
	explicit Player() {};
	virtual ~Player() {};

	// Object을(를) 통해 상속됨
	virtual HRESULT ReadObject() override;
	virtual int UpdateObject() override;
	virtual void LateUpdateObject() override;
	virtual void RenderObject(HDC _hdc) override;
	virtual void ReleaseObject() override;

private:
	float speed;
};


#endif //__PLAYER_H__
