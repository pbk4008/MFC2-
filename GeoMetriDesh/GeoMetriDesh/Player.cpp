#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "LineMgr.h"


#include "ObjectManager.h"

Player::Player()
    : m_fAngle(0.f), flyState(true)
{
}

Player::~Player()
{
    ReleaseObject();
}

HRESULT Player::ReadObject()
{
    if (flyState == false)
    {// 텍스트 정보를 추가하고 불러야함
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

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////


    if (flyState == true)
    {
        TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Plane.png", L"Plane");
        // 부르기!
        pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Plane");

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

        // 나락(?)
        GRAVITIY = 5.8f;
        fallY = 0;
        fallState = true;

        SetObjectInfo(); // 필수!
        return S_OK;
    }
}

int Player::UpdateObject()
{
    KeyChecking();

    if (flyState)
        PlaneMovement();

    if (flyState == false)
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
    if (flyState == false)
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
    if (flyState == true)
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

}

void Player::ReleaseObject()
{
    SAFE_DELETE(keyMgr);
}

void Player::Jumping()
{
    if (flyState == false)
    {
        if (!jumpState) {
            return;
        }
        // 내가 떨어질 Y값을 담을 변수
        float fY = 0.f;
        bool lineCheck = CLineMgr::GetInstance()->CollisionLine(info.pos.x, rc.bottom, &fY);

        if (lineCheck) {
            jumpTime += 0.6f;
            rc.bottom = jumpY - ((jumpPower * jumpTime) - (0.5f * GRAVITIY * jumpTime * jumpTime));

            if (lineCheck && rc.bottom >= fY) {
                jumpState = false;
                jumpTime = 0.f;
                rc.bottom = fY;
            }
        }
        else if (lineCheck) {
            rc.bottom = fY;
        }
        info.pos.y = rc.bottom - (info.size.y * 0.5f);
    }
}

void Player::PlaneMovement()
{
    if (fallState == false)
        info.pos.y -= GRAVITIY;
    else
    {
        info.pos.y += GRAVITIY;

        float fY = 0.f;
        bool lineCheck = CLineMgr::GetInstance()->CollisionLine(info.pos.x, rc.bottom, &fY);

        if (lineCheck && info.pos.y >= fY)
        {
            info.pos.y = fY;
            m_fAngle = 0;
        }
    }
}


void Player::KeyChecking()
{
    if (flyState == false)
    {
        if (!jumpState) {
            // 풀링 테스트
            if (keyMgr->KeyPressing(VK_SPACE)) {
                jumpY = info.pos.y;
                jumpState = true;
            };
        }
 
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    if (flyState == true)
    {       
            if (keyMgr->KeyPressing(VK_SPACE)) //         
                fallState = false;          
            else
                fallState = true;               
    }
}

void Player::WriteMatrix()
{
    // 크 * 자 * 이 * 공 * 부 
    // 기   전   동   전   모
    if (flyState == false)
    {
        D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
        //m_fAngle += 5.f;

        D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
        D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, 0.f);

        matWorld = matScale * matRotZ * matTrans;

        GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    if (flyState == true)
    {
        D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
        //m_fAngle += 5.f;

        D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
        D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y - 5.f, 0.f);

        matWorld = matScale * matRotZ * matTrans;

        GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
    }
}

void Player::RotateAngle()
{
    if (flyState == false)
    {// 임시방편!!
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

    ////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////

    if (flyState == true)
    {
        if (fallState)
        {
            m_fAngle += 2.f;

            if (m_fAngle >= 45) {
                m_fAngle = 45;
            }
        }
        else        
            m_fAngle -= 1.f;               
    }
}