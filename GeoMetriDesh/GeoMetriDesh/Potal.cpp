#include "framework.h"
#include "Potal.h"
#include"TextureManager.h"
#include"ScrollMgr.h"
#include "ObjectManager.h"
HRESULT CPotal::ReadObject()
{
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Potal", L"Potal", iIndex);
    info.size = { 100.f,200.f,0.f };
    SetObjectInfo();
    return S_OK;
}

int CPotal::UpdateObject()
{
    //posX = 800;
    float fX = CScrollMgr::GetInstance()->getUpdateScrollX();
    info.pos.x = (posX - fX);
    UpdateObjectInfo();
    return 0;
}

void CPotal::LateUpdateObject()
{
}

void CPotal::RenderObject()
{
    
    D3DXMATRIX matWorld;
    D3DXMatrixTranslation(&matWorld, info.pos.x, info.pos.y, 0.f);

    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

    GraphicDevice::GetInstance()->GetSprite()->Draw(pTextInfo->texture, nullptr,
        &centerVec,
        nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

    // 라인 보이기 체크(키보드 L or K)
    if (ObjectManager::GetInstance()->GetShowLineCheck()) {
        // 그래픽디바이스를 끄고  다시 그려야 한다!
        GraphicDevice::GetInstance()->GetSprite()->End();
        GraphicDevice::GetInstance()->GetLine()->SetWidth(2.f);
        GraphicDevice::GetInstance()->GetLine()->Draw(lineList, 5, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B));
        GraphicDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
    }
}

void CPotal::ReleaseObject()
{
}
