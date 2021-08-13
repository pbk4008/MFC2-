#pragma once
#ifndef __GRAPHIC_DEVICE_H__
#define __GRAPHIC_DEVICE_H__


class GraphicDevice
{
	DECLARE_SINGLETON(GraphicDevice)
public:
	explicit GraphicDevice();
	virtual ~GraphicDevice();
public:
	HRESULT ReadyGraphicDevice();

	LPDIRECT3DDEVICE9 GetDevice() { return mDevice; };
	LPD3DXSPRITE GetSprite() { return mSprite; };
	void ReleaseDevice();

	void RenderBegin();
	void RenderEnd();

public:
	// 사용할 장치 받아오기
	LPDIRECT3D9 mSdk;

	LPD3DXSPRITE mSprite;

	// 실질적으로 사용할 장치
	LPDIRECT3DDEVICE9 mDevice;

};





#endif // !__GRAPHIC_DEVICE_H__


