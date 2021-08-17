#pragma once
#ifndef __TITLE_H__
#define __TITLE_H__

#include "Object.h"
class Title : public Object
{
	// Object��(��) ���� ��ӵ�
	virtual HRESULT ReadObject() override;
	virtual int UpdateObject() override;
	virtual void LateUpdateObject() override;
	virtual void RenderObject() override;
	virtual void ReleaseObject() override;

	void SetMatrix();

	void SetCheck(bool _b) { imageCheck = _b; };

private:
	bool imageCheck;
	DWORD dwTime;
	int setImage;
	float size;
};


#endif // !__TITLE_H__