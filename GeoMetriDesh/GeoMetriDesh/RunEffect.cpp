#include "framework.h"
#include "RunEffect.h"
#include "TextureManager.h"
#include "ObjectManager.h"

HRESULT RunEffect::ReadObject()
{
    TextureManager::GetInstance()->InsertTexture(
        TextureManager::MULTI,
        L"../Texture/Effect/Run%d.png",
        L"Effect",
        L"Run",
        2
    );
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Effect", L"Run", 0);

    info.dir = {1.f, 0.f, 0.f};

    rgb.A = 255;
    rgb.R = 255;
    rgb.G = 255;
    rgb.B = 255;

    scaleSize = 1.f;

    SetObjectInfo();
    return S_OK;
}

int RunEffect::UpdateObject()
{
    return NOEVENT;
}

void RunEffect::LateUpdateObject()
{
}

void RunEffect::RenderObject()
{
    D3DXMATRIX matScale, matTrans;

    D3DXMatrixScaling(&matScale, scaleSize, scaleSize, 0.f);
    D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, 0.f);
    info.mat = matScale * matTrans;
    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&info.mat);

    
    info.pos = ObjectManager::GetInstance()->GetPlayer()->GetPos();


    DrawImage();
}

void RunEffect::ReleaseObject()
{
}
