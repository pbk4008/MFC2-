#include "framework.h"
#include "Menu.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
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

    TextureManager::GetInstance()->InsertTexture(
        TextureManager::SINGLE,
        L"../Texture/BackGround/Square2.png",
        L"BackGround2");

    // RGB값 조정 가능
    rgb.A = 150;
    rgb.R = 0;
    rgb.G = 0;
    rgb.B = 255;


    ObjectManager::GetInstance()->InsertObject<Title>(ObjectManager::UI);
    ObjectManager::GetInstance()->InsertObject<PlayBtn>(ObjectManager::UI);

    CScrollMgr::GetInstance()->reSetSpeed();
    CScrollMgr::GetInstance()->setSpeed(1.f);


    CScrollMgr::GetInstance()->reSetBackSpeed();
    CScrollMgr::GetInstance()->setBackSpeed(2.f);


    subScroll = 0;

    CSoundMgr::Get_Instance()->PlayBGM(L"Menu.mp3");

    return S_OK;
}

int Menu::Update()
{
    CScrollMgr::GetInstance()->XUpdate();

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
  
    D3DXMATRIX matScale, matTrans;
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
    D3DXMatrixTranslation(&matTrans, 0.f, 0.f, 0.f);
    matScale*= matTrans;
    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matScale);

    float scollX = CScrollMgr::GetInstance()->getBackGroundScrollX();

    TEXTINFO* pTextInfo1 = TextureManager::GetInstance()->GetTextInfo(L"BackGround");
    D3DXVECTOR3 centerVec1 = {
       +scollX,
        0.f,
        0.f
    };

    D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
    D3DXMatrixTranslation(&matTrans, WINCX, 0.f, 0.f);
    matScale *= matTrans;
    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matScale);

    GraphicDevice::GetInstance()->GetSprite()->Draw(
        pTextInfo1->texture, nullptr, &centerVec1,nullptr,D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
    );

    TEXTINFO* pTextInfo2 = TextureManager::GetInstance()->GetTextInfo(L"BackGround2");
    D3DXVECTOR3 centerVec2 = {
       pTextInfo1->imageInfo.Width+(+scollX),
        0.f,
        0.f
    };

    GraphicDevice::GetInstance()->GetSprite()->Draw(
        pTextInfo2->texture, nullptr, &centerVec2, nullptr, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B)
    );


    // 배경 끝나고
    if (scollX >= pTextInfo1->imageInfo.Width) {
        CScrollMgr::GetInstance()->setBackGroundScrollX(0.f);
    }

    ObjectManager::GetInstance()->Render();
}

void Menu::Release()
{
    CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
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
        if (KeyManager::GetInstance()->KeyDown(VK_LBUTTON)) {
            //TextureManager::GetInstance()->Release();

            CSoundMgr::Get_Instance()->PlaySound(L"playSound_01.mp3", CSoundMgr::UI);

            SceneManager::GetInstance()->ChangeScene(SceneManager::STAGE);
        }
    }
}
