#include "framework.h"
#include "Title.h"
#include "TextureManager.h"

HRESULT Title::ReadObject()
{
    // 플레이 버튼
    TextureManager::GetInstance()->InsertTexture(
        TextureManager::SINGLE,
        L"../Texture/Menu/Title.png",
        L"Title");
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Title");

    info.pos = { 450, 100.f, 0.f };
    info.size = { pTextInfo->imageInfo.Width * 0.5f, pTextInfo->imageInfo.Height * 0.5f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    rgb.A = 255;
    rgb.R = 255;
    rgb.G = 0;
    rgb.B = 0;

    SetObjectInfo(); // 필수!
    return S_OK;
}

int Title::UpdateObject()
{
    return NOEVENT;
}

void Title::LateUpdateObject()
{
    UpdateObjectInfo();
}

void Title::RenderObject()
{
    SetMatrix();
    DrawImage();
}

void Title::ReleaseObject()
{
}

void Title::SetMatrix()
{
    D3DXMATRIX matScale;

    D3DXMatrixScaling(&matScale, 0.9f, 0.9f, 0.9f);
    info.mat = matScale;
    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&info.mat);
}
