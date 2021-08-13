#include "framework.h"
#include "Menu.h"
#include "TextureManager.h"

HRESULT Menu::Initialize()
{
    // 출력할 이미지!

    //// 싱글 텍스쳐
    //TextureManager::GetInstance()->InsertTexture(
    //    TextureManager::SINGLE, 
    //    L"../Texture/DaHyounNim.jpg",
    //    L"Menu" );


    return S_OK;
}

int Menu::Update()
{
    return NOEVENT;
}

void Menu::LateUpdate()
{
}

void Menu::Render()
{
   /* TEXTINFO* pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Menu");

    D3DXVECTOR3 centerVec = {
        pTextInfo->imageInfo.Width * 0.5f,
        pTextInfo->imageInfo.Height * 0.5f,
        0.f
    };

    GraphicDevice::GetInstance()->GetSprite()->Draw(
        pTextInfo->texture, nullptr, nullptr,nullptr,D3DCOLOR_ARGB(255,255,255,255)
    );*/

}

void Menu::Release()
{
}
