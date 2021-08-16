#include "framework.h"
#include "PlayBtn.h"
#include "TextureManager.h"

HRESULT PlayBtn::ReadObject()
{
    checkClickEvent = true;

    // 플레이 버튼
    TextureManager::GetInstance()->InsertTexture(
        TextureManager::SINGLE,
        L"../Texture/Menu/PlayBtn.png",
        L"PlayBtn");
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"PlayBtn");

    info.pos = { float(WINCX>>1), 350, 0.f };
    info.size = { 200.f, 200.f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    rgb.A = 255;
    rgb.R = 255;
    rgb.G = 0;
    rgb.B = 0;

    SetObjectInfo(); // 필수!
    return S_OK;
}

int PlayBtn::UpdateObject()
{
    return NOEVENT;
}

void PlayBtn::LateUpdateObject()
{
    UpdateObjectInfo();
}

void PlayBtn::RenderObject()
{
    SetMatrix();
    DrawImage();
}

void PlayBtn::ReleaseObject()
{
    deadCheck = true;
}

void PlayBtn::SetMatrix()
{
    D3DXMATRIX matScale;
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matScale);
}
