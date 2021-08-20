#pragma once
#include "Object.h"
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include"TextureManager.h"
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
	bool getGod() { return m_bGod; }
	void setFly(bool _bFly) { flyState = _bFly; pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Plane");}
	void setEnd(bool _bEnd) { ending = _bEnd; }
private:
	void Ending();
private:
	float		m_fAngle;

	KeyManager* keyMgr;
	float argPos;
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotZ;
	D3DXMATRIX	matWorld;
	D3DXMATRIX  matTrans;
	D3DXMATRIX  matTotal;
	float GRAVITIY;
	bool fallState;
	bool flyState;


	bool jumpState;
	float jumpTime;
	float jumpPower;
	float jumpY;

	float fallY;

	DWORD effectDelay;

	bool fallRotateAngle;

	float fStartY;

	bool ending;
	bool m_bGod=false;
};


#endif //__PLAYER_H__
