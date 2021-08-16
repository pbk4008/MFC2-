#include "framework.h"
#include "Menu.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "PlayBtn.h"
#include "Title.h"


HRESULT Menu::Initialize()
{
    btnCollisionCheck = false;


    // 배경!
    TextureManager::GetInstance()->InsertTexture(
        TextureManager::SINGLE, 
        L"../Texture/BackGround/Square.png",
        L"BackGround" );
    // RGB값 조정 가능
    rgb.A = 150;
    rgb.R = 0;
    rgb.G = 0;
    rgb.B = 255;

    ObjectManager::GetInstance()->InsertObject<Title>(ObjectManager::UI);
    ObjectManager::GetInstance()->InsertObject<PlayBtn>(ObjectManager::UI);

    return S_OK;
}

int Menu::Update()
{
    ObjectManager::GetInstance()->Update();
    SetPlayBtn();
    KeyChecking();
    return S_OK;
}

void Menu::LateUpdate()
{
    ObjectManager::GetInstance()->LateUpdate();
}

void Menu::Render()
{
    TEXTINFO* pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"BackGround");

    D3DXVECTOR3 centerVec = {
        float(pTextInfo->imageInfo.Width >> 1),
        float(pTextInfo->imageInfo.Height >> 1),
        0.f
    };

    GraphicDevice::GetInstance()->GetSprite()->Draw(
        pTextInfo->texture, nullptr, nullptr,nullptr,D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
    );
    // 배경 끝나고

    ObjectManager::GetInstance()->Render();
}

void Menu::Release()
{
    ObjectManager::GetInstance()->ReleaseObject(ObjectManager::UI);
}

void Menu::SetPlayBtn()
{
    list<Object*> uiList = ObjectManager::GetInstance()->GetList(ObjectManager::UI);

    POINT pt = {};
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);

    WCHAR szBuff[32] = L"";
    swprintf_s(szBuff, L"btnCollisionCheck : %d, %d", pt.x, pt.y);
    SetWindowText(g_hWnd, szBuff);

    for (auto rUi : uiList) {

        RECT rc = rUi->GetRect();

        if (rUi->GetCheckClickEvent() && 
            PtInRect(&rUi->GetRect(), pt)) {
            btnCollisionCheck = true;
        }
        else {
            btnCollisionCheck = false;
        }
    }
}

void Menu::KeyChecking()
{
    if (btnCollisionCheck) {
        if (KeyManager::GetInstance()->KeyPressing(VK_LBUTTON)) {
            //TextureManager::GetInstance()->Release();
            SceneManager::GetInstance()->ChangeScene(SceneManager::STAGE);
        }
    }
}
