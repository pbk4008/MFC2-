#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

class Scene
{
public:
	inline explicit Scene() {
		ZeroMemory(&rgb, sizeof(rgb));
	};
	inline virtual ~Scene() {};

	inline virtual HRESULT Initialize() PURE;
	inline virtual int Update() PURE;
	inline virtual void LateUpdate() PURE;
	inline virtual void Render() PURE;
	inline virtual void Release() PURE;

protected:
	ARGB rgb;
};


#endif // !__SCENE_H__