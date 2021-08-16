#include "framework.h"
#include "Menu.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "ScrollMgr.h"
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

    //TextureManager::GetInstance()->InsertTexture(
    //    TextureManager::SINGLE,
    //    L"../Texture/BackGround/Square2.png",
    //    L"BackGround2");

    // RGB값 조정 가능
    rgb.A = 150;
    rgb.R = 0;
    rgb.G = 0;
    rgb.B = 255;


    ObjectManager::GetInstance()->InsertObject<Title>(ObjectManager::UI);
    ObjectManager::GetInstance()->InsertObject<PlayBtn>(ObjectManager::UI);

    CScrollMgr::GetInstance()->reSetSpeed();
    CScrollMgr::GetInstance()->setSpeed(2.f);
    subScroll = 0;

    return S_OK;
}

int Menu::Update()
{
    CScrollMgr::GetInstance()->XUpdate();
    subScroll++;

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
    float scollX = CScrollMgr::GetInstance()->getUpdateScrollX();
    TEXTINFO* pTextInfo1 = TextureManager::GetInstance()->GetTextInfo(L"BackGround");
    D3DXVECTOR3 centerVec1 = {
       -scollX,
        0.f,
        0.f
    };

    GraphicDevice::GetInstance()->GetSprite()->Draw(
        pTextInfo1->texture, nullptr, nullptr,&centerVec1,D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
    );
    // 배경 끝나고

    // 아 모르겠다!!! 내일한다!!
    WCHAR szBuff[50] = L"";
    swprintf_s(szBuff, L"%d", subScroll);
    SetWindowText(g_hWnd, szBuff);

    if (subScroll >= 100) {
        TEXTINFO* pTextInfo2 = TextureManager::GetInstance()->GetTextInfo(L"BackGround");
        D3DXVECTOR3 centerVec2 = {
           pTextInfo1->imageInfo.Width + (-scollX),
            0.f,
            0.f };

        GraphicDevice::GetInstance()->GetSprite()->Draw(
            pTextInfo2->texture, nullptr, nullptr, &centerVec2, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
        );
        subScroll = 0;
    }

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

    for (auto rUi : uiList) {
        if (rUi->GetCheckClickEvent() && 
            PtInRect(&rUi->GetRect(), pt)) {
            rUi->SetCheck(true);
            btnCollisionCheck = true;
        }
        else {
            rUi->SetCheck(false);
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
