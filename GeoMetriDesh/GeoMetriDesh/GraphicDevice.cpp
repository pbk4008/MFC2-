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
	mSdk = Direct3DCreate9(D3D_SDK_VERSION); // ��ġ �ҷ�����

	D3DCAPS9 deviceCaps = {};

	if (FAILED(mSdk->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &deviceCaps))) {
		return E_FAIL;
	} // ��ġ �˻�

	DWORD vp = 0;
	// ��������μ��� �˻�
	if (deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; // �̰Ÿ� �� ���� �Ͻ� (�׷��� ī�尡 ���� ��)


	// �ϴ� �������� �����ϽŰ� �״�� ������
	// �߰����� ���� ������ �ʿ��� �� �����ּ���

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD - ����ü�� ����� ����ϰڴ�. 
	// ����ü�� ����� ������ۿ� �ĸ���۸� �ΰ� �ΰ� 
	// �ĸ鿡�� �׸��� �׸� �� ������ۿ� ��ü�ϴ� ���. 
	// �츮�� ������ ��� �ߴ� ������۸��� ������ۿ� �����Ͽ� �׸��� ����� ����Ϳ� ���� 
	// ������ ������. ������۸��� ���� ȣȯ ������ �����ϸ� �ǰڴ�. 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = TRUE; // ��带 ��� �� ���̳� ���� !?  â���� ��üȭ�� ���� 
	// TRUE - â��� , FALSE - ��üȭ�� 
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// �׷���ī�� ��ġ �غ�
	if (FAILED(mSdk->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &mDevice)))
	{
		return E_FAIL;
	}

	// ��������Ʈ == �׸� �׸��� ����
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
	// ����� ��Ʈ
	//lstrcpy(tDesc.FaceName, L"");

	// ��Ʈ ����
	if (FAILED(D3DXCreateFontIndirectW(mDevice, &tDesc, &mFont))) {
		return E_FAIL;
	}
	// ���� ����
	if (FAILED(D3DXCreateLine(mDevice, &mLine))) {
		return E_FAIL;
	}

	//g_hDC = mDevice->GetBackBuffer();

	return S_OK;
}


void GraphicDevice::ReleaseDevice()
{
	// ���۷����� ���� ��ġ���� �����ϱ�!
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
