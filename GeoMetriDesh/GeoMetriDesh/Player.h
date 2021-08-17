#pragma once
#include "Object.h"
#ifndef __PLAYER_H__
#define __PLAYER_H__

class KeyManager;
class Player : public Object
{
public:
	explicit Player();
	virtual ~Player();

	// Object을(를) 통해 상속됨
	virtual HRESULT ReadObject() override;
	virtual int UpdateObject() override;
	virtual void LateUpdateObject() override;
	virtual void RenderObject() override;
	virtual void ReleaseObject() override;

	void KeyChecking();
	void WriteMatrix();

private:
	float		m_fAngle;

	KeyManager* keyMgr;

	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotZ;
	D3DXMATRIX	matWorld;
	D3DXMATRIX  matTrans;
};


#endif //__PLAYER_H__
