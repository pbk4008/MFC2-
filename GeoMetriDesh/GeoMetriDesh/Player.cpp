#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "LineMgr.h"

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
    info.pos = { 100.f, 100.f, 0.f }; //xyz
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

    jumpState = false;
    jumpTime = 0.f;
    jumpPower = 20.f;
    jumpY = 0;


    SetObjectInfo(); // 필수!
    return S_OK;
}

int Player::UpdateObject()
{
    KeyChecking();
    Jumping();
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

    DrawImage(); // 필수!
}

void Player::ReleaseObject()
{
    SAFE_DELETE(keyMgr);
}

void Player::Jumping()
{
  



    // 내가 떨어질 Y값을 담을 변수
    float fY = 0.f;
    bool lineCheck = CLineMgr::GetInstance()->CollisionLine(info.pos.x, info.pos.y, &fY);


    if (lineCheck) {

        jumpTime += 0.2f;
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
    // 풀링 테스트
    if (keyMgr->KeyDown(VK_SPACE)) {
        int iCount = 0;
        for (0; iCount <= 18; ++iCount)
        {
            m_fAngle += 5.f;
        }
        iCount = 0;

        jumpState = true;
    };


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
    D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);

    matWorld = matScale * matRotZ * matTrans;



    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
}
