#pragma once
#ifndef __RUNEFFECT_H__
#define __RUNEFFECT_H__
#include "Object.h"
class RunEffect : public Object
{
	// Object을(를) 통해 상속됨
	virtual HRESULT ReadObject() override;
	virtual int UpdateObject() override;
	virtual void LateUpdateObject() override;
	virtual void RenderObject() override;
	virtual void ReleaseObject() override;

	void Offset();
	void DeadEffect();

private:
	float scaleSize;
	Object* mPlayer;
};


#endif // !__RUNEFFECT_H__