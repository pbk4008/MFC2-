#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "LineMgr.h"


#include "ObjectManager.h"

Player::Player()
    : m_fAngle(0.f)
{
}

Player::~Player()
{
    ReleaseObject();
}

HRESULT Player::ReadObject()
{
   // 텍스트 정보를 추가하고 불러야함
    // 추가!
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Player.png", L"Player");
    // 부르기!
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Player");

    // info의 pos, size, dir는 직접 지정해줘야 한다
    info.pos = { 300.f, 100.f, 0.f }; //xyz
    info.size = { 100.f, 100.f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    rgb.A = 255;
    rgb.R = 255;
    rgb.G = 0;
    rgb.B = 0;

    // 반복 연산을 줄이기 위해 선언!
    keyMgr = KeyManager::GetInstance();

    // 점프!
    GRAVITIY = 9.8f;

    jumpState = true;
    jumpTime = 100.f;
    jumpPower = 70.f;
    jumpY = 0;


    SetObjectInfo(); // 필수!
    return S_OK;
}

int Player::UpdateObject()
{
    KeyChecking();
    Jumping();
    RotateAngle();
    return NOEVENT;
}

void Player::LateUpdateObject()
{

    UpdateObjectInfo(); // 필수!
}

void Player::RenderObject()
{
    WriteMatrix();
    float fCenterX = info.pos.x * 0.5f;
    float fCenterY = info.pos.y * 0.5f;
   // D3DXVECTOR3 spinCenter{ (info.pos.x * 0.5f), (info.pos.y * 0.5f), 0.f };

    GraphicDevice::GetInstance()->GetSprite()->Draw(pTextInfo->texture, nullptr,
        &centerVec,
        nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

    //DrawImage(); // 필수!


    // 라인 보이기 체크(키보드 L or K)
    if (ObjectManager::GetInstance()->GetShowLineCheck()) {
        // 그래픽디바이스를 끄고  다시 그려야 한다!
        GraphicDevice::GetInstance()->GetSprite()->End();
        GraphicDevice::GetInstance()->GetLine()->SetWidth(2.f);
        GraphicDevice::GetInstance()->GetLine()->Draw(lineList, 5, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B));
        GraphicDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
    }

}

void Player::ReleaseObject()
{
    SAFE_DELETE(keyMgr);
}

void Player::Jumping()
{
    if (!jumpState) {
        return;
    }

    // 내가 떨어질 Y값을 담을 변수
    float fY = 0.f;
    bool lineCheck = CLineMgr::GetInstance()->CollisionLine(info.pos.x, info.pos.y, &fY);


    if (lineCheck) {

        jumpTime += 0.6f;
        info.pos.y = jumpY - ((jumpPower * jumpTime) - (0.5f * GRAVITIY * jumpTime * jumpTime));

        if (lineCheck && info.pos.y >= fY) {
            jumpState = false;
            jumpTime = 0.f;
            info.pos.y = fY;

        }
    }
    else if(lineCheck){
        info.pos.y = fY;
    }


}

void Player::KeyChecking()
{
    if (!jumpState) {
        // 풀링 테스트
        if (keyMgr->KeyDown(VK_SPACE)) {
           
            jumpY = info.pos.y;
            jumpState = true;
        };
    }
    //if (keyMgr->KeyPressing('W')) {
    //    SetDeadCheck(false);
    //};

    //// 키 테스트
    //if (keyMgr->KeyPressing(VK_LEFT)) {
    //    info.pos.x -= 5.f;
    //}
    //if (keyMgr->KeyPressing(VK_RIGHT)) {
    //    info.pos.x += 5.f;
    //}
    //if (keyMgr->KeyPressing(VK_UP)) {
    //    info.pos.y -= 5.f;
    //}
    //if (keyMgr->KeyPressing(VK_DOWN)) {
    //    info.pos.y += 5.f;
    //}

}

void Player::WriteMatrix()
{
    // 크 * 자 * 이 * 공 * 부 
    // 기   전   동   전   모
    
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
    //m_fAngle += 5.f;

    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, 0.f);

    matWorld = matScale * matRotZ * matTrans;



    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
}

void Player::RotateAngle()
{
    // 임시방편!!
    if (jumpState) {

        m_fAngle += 5.f;

        if (m_fAngle >= 90) {
            m_fAngle = 90;
        }
    }
    else {
        m_fAngle = 0;
    }

}
