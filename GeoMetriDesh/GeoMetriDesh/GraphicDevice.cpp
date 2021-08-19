#include "framework.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(GraphicDevice)
GraphicDevice::GraphicDevice()
{
}

GraphicDevice::~GraphicDevice()
{
	ReleaseDevice();
}

HRESULT GraphicDevice::ReadyGraphicDevice()
{
	mSdk = Direct3DCreate9(D3D_SDK_VERSION); // 장치 불러오기

	D3DCAPS9 deviceCaps = {};

	if (FAILED(mSdk->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &deviceCaps))) {
		return E_FAIL;
	} // 장치 검사

	DWORD vp = 0;
	// 버츄얼프로세싱 검사
	if (deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; // 이거면 컴 사라고 하심 (그래픽 카드가 없을 시)


	// 일단 선생님이 셋팅하신거 그대로 가져옴
	// 추가적인 설정 변경이 필요할 시 말씀주세요

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD - 스왑체인 방식을 사용하겠다. 
	// 스왑체인 방식은 전면버퍼와 후면버퍼를 두개 두고 
	// 후면에서 그림을 그린 후 전면버퍼와 교체하는 방식. 
	// 우리가 이전에 사용 했던 더블버퍼링은 전면버퍼에 복사하여 그리는 방식을 썼던것에 비해 
	// 가볍고 빠르다. 더블버퍼링의 상위 호환 정도로 생각하면 되겠다. 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = TRUE; // 모드를 어떻게 할 것이냐 어떤모드 !?  창모드냐 전체화면 모드냐 
	// TRUE - 창모드 , FALSE - 전체화면 
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// 그래픽카드 장치 준비
	if (FAILED(mSdk->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &mDevice)))
	{
		return E_FAIL;
	}

	// 스프라이트 == 그림 그리는 도구
	if (FAILED(D3DXCreateSprite(mDevice, &mSprite)))
	{
		return E_FAIL;
	}

	D3DXFONT_DESCW tDesc;
	ZeroMemory(&tDesc, sizeof(D3DXFONT_DESCW));
	tDesc.Height = 20;
	tDesc.Width = 15;
	tDesc.Weight = FW_HEAVY;
	tDesc.CharSet = HANGUL_CHARSET;
	// 사용할 폰트
	//lstrcpy(tDesc.FaceName, L"");

	// 폰트 생성
	if (FAILED(D3DXCreateFontIndirectW(mDevice, &tDesc, &mFont))) {
		return E_FAIL;
	}
	// 라인 생성
	if (FAILED(D3DXCreateLine(mDevice, &mLine))) {
		return E_FAIL;
	}

	//g_hDC = mDevice->GetBackBuffer();

	return S_OK;
}


void GraphicDevice::ReleaseDevice()
{
	// 레퍼런스로 잡힌 장치부터 삭제하기!
	if (mDevice) {
		mDevice->Release();
	}

	if (mSdk) {
		mSdk->Release();
	}
}

void GraphicDevice::RenderBegin()
{
	mDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(50, 0, 0, 100), 1, 0);
	mDevice->BeginScene();
	mSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void GraphicDevice::RenderEnd()
{
	mSprite->End();
	mDevice->EndScene();
	mDevice->Present(nullptr, nullptr, nullptr, nullptr);

}
