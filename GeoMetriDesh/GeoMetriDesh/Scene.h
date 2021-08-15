#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

class Scene
{
public:
	inline explicit Scene() {};
	inline virtual ~Scene() {};

	inline virtual HRESULT Initialize() PURE;
	inline virtual int Update() PURE;
	inline virtual void LateUpdate() PURE;
	inline virtual void Render() PURE;
	inline virtual void Release() PURE;


};


#endif // !__SCENE_H__