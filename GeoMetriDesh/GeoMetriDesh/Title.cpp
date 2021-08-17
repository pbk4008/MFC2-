#include "framework.h"
#include "Title.h"
#include "TextureManager.h"

HRESULT Title::ReadObject()
{
    // 플레이 버튼
    TextureManager::GetInstance()->InsertTexture(
        TextureManager::MULTI,
        L"../Texture/Menu/Title/Title%d.png",
        L"Title",
        L"Title",
        6
    );

    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Title", L"Title", 0);

    info.pos = { 450, 100.f, 0.f };
    info.size = { pTextInfo->imageInfo.Width * 0.5f, pTextInfo->imageInfo.Height * 0.5f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    rgb.A = 255;
    rgb.R = 255;
    rgb.G = 0;
    rgb.B = 0;

    size = 0.9f;
    setImage = 0;
    dwTime = GetTickCount64();

    imageCheck = false;

    SetObjectInfo(); // 필수!
    return S_OK;
}

int Title::UpdateObject()
{
    if (dwTime + 40 < GetTickCount64()) {
        setImage++;
        dwTime = GetTickCount64();
    }

    return NOEVENT;
}

void Title::LateUpdateObject()
{
    if (6 == setImage) {
        setImage = 0;
    }

   UpdateObjectInfo();
}

void Title::RenderObject()
{
   pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Title", L"Title", setImage);
    SetMatrix();
    DrawImage();
}

void Title::ReleaseObject()
{
}

void Title::SetMatrix()
{
    D3DXMATRIX matScale;

    D3DXMatrixScaling(&matScale, size, size, 0.f);
    info.mat = matScale;
    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&info.mat);
}
