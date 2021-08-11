#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object
{
public:
	inline explicit Object() {};
	inline ~Object() {};

	inline virtual HRESULT ReadObject() PURE;
	inline virtual int UpdateObject() PURE;
	inline virtual void LateUpdateObject() PURE;
	inline virtual void RenderObject(HDC _hdc) PURE;
	inline virtual void ReleaseObject() PURE;

protected:
	INFO info;
};


#endif // !__OBJECT_H__