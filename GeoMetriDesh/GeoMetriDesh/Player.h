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

	void Jumping();
	void PlaneMovement();

	void KeyChecking();
	void WriteMatrix();
	void RotateAngle();
	void SetEffect();

private:
	float		m_fAngle;

	KeyManager* keyMgr;

	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotZ;
	D3DXMATRIX	matWorld;
	D3DXMATRIX  matTrans;

	float GRAVITIY;
	bool fallState;
	bool flyState;


	bool jumpState;
	float jumpTime;
	float jumpPower;
	float jumpY;

	float fallY;

	DWORD effectDelay;
};


#endif //__PLAYER_H__
