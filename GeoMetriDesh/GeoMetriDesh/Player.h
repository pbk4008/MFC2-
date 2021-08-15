#pragma once
#include "Object.h"
#ifndef __PLAYER_H__
#define __PLAYER_H__

class KeyManager;
class Player : public Object
{
public:
	explicit Player() {};
	virtual ~Player() {};

	// Object��(��) ���� ��ӵ�
	virtual HRESULT ReadObject() override;
	virtual int UpdateObject() override;
	virtual void LateUpdateObject() override;
	virtual void RenderObject() override;
	virtual void ReleaseObject() override;

	void KeyChecking();

private:
	float speed; // �ʿ� ������?
	KeyManager* keyMgr;
};


#endif //__PLAYER_H__
