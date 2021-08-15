#include "framework.h"
#include "Menu.h"
#include "TextureManager.h"
//#include "KeyManager.h"
#include "SceneManager.h"



HRESULT Menu::Initialize()
{
    // ����� �̹���!

    // �̱� �ؽ���
    TextureManager::GetInstance()->InsertTexture(
        TextureManager::SINGLE, 
        L"../Texture/DaHyounNim.jpg",
        L"Menu" );


    return S_OK;
}

int Menu::Update()
{

    //if (KeyManager::GetInstance()->KeyPressing('W')) {
    //    SceneManager::GetInstance()->ChangeScene(SceneManager::LOGO);
    //}

    return NOEVENT;
}

void Menu::LateUpdate()
{
}

void Menu::Render()
{
    TEXTINFO* pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Menu");

    D3DXVECTOR3 centerVec = {
        float(pTextInfo->imageInfo.Width >> 1),
        float(pTextInfo->imageInfo.Height >> 1),
        0.f
    };

    GraphicDevice::GetInstance()->GetSprite()->Draw(
        pTextInfo->texture, nullptr, nullptr,nullptr,D3DCOLOR_ARGB(255,255,255,255)
    );

}

void Menu::Release()
{
}
