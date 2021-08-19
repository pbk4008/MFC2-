#include "framework.h"
#include "RunEffect.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "ScrollMgr.h"

HRESULT RunEffect::ReadObject()
{
    TextureManager::GetInstance()->InsertTexture(
        TextureManager::MULTI,
        L"../Texture/Effect/Run%d.png",
        L"Effect",
        L"Run",
        2
    );
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Effect", L"Run", 1);
    

    //info.pos = ObjectManager::GetInstance()->GetPlayer()->GetPos();
    info.dir = {1.f, 0.f, 0.f};

    rgb.A = 100;
    rgb.R = 255;
    rgb.G = 237;
    rgb.B = 0;

    scaleSize = 1.f;

    //CScrollMgr::GetInstance()->XUpdate();
    //CScrollMgr::GetInstance()->reSetSpeed();
    //CScrollMgr::GetInstance()->setSpeed(3.f);

    SetObjectInfo();
    return S_OK;
}

int RunEffect::UpdateObject()
{
    Offset();
    DeadEffect();


    if (deadCheck) {
        scaleSize = 1.f;
    }

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
    
    GraphicDevice::GetInstance()->GetSprite()->Draw(pTextInfo->texture, nullptr,
        &centerVec,
        nullptr, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B));

    //DrawImage();
}

void RunEffect::ReleaseObject()
{
}

void RunEffect::DeadEffect()
{
    scaleSize -= 0.02f;

    if (scaleSize <= 0) {
        scaleSize = 0;
        deadCheck = true;
    }


}

void RunEffect::Offset()
{
    float scrollX = CScrollMgr::GetInstance()->getScrollX();

    info.pos.x -= 4.f;
    info.pos.y += 0.5f;
}
