#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "RunEffect.h"
#include "ObjectManager.h"
#include "Land.h"

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
    // �ؽ�Ʈ ������ �߰��ϰ� �ҷ�����
    // �߰�!
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Player.png", L"Player");
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Plane.png", L"Plane");
    // �θ���!
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Player");
    


    // info�� pos, size, dir�� ���� ��������� �Ѵ�
    info.pos = { 300.f, 400.f, 0.f }; //xyz
    info.size = { 100.f, 100.f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    rgb.A = 255;
    rgb.R = 255;
    rgb.G = 0;
    rgb.B = 0;

    // �ݺ� ������ ���̱� ���� ����!
    keyMgr = KeyManager::GetInstance();


    // ����!
    GRAVITIY = 9.8f;
    jumpState = false;
    jumpTime = 0.f;
    jumpPower = 70.f;
    jumpY = 0;

    fallY = 0;
    fallState = true;
    flyState = false;
    fallRotateAngle = false;

    effectDelay = GetTickCount();

    ending = false;

    SetObjectInfo(); // �ʼ�!
    return S_OK;
}

int Player::UpdateObject()
{
    if (ending) {
        Ending();
    }
    else
    {
    KeyChecking();
    if (flyState)
        PlaneMovement();

    if (flyState == false)
        Jumping();

    RotateAngle();
    SetEffect();

    }
    return NOEVENT;
}

void Player::LateUpdateObject()
{
    UpdateObjectInfo(); // �ʼ�!
}

void Player::RenderObject()
{
    if (ending) {

        GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

        GraphicDevice::GetInstance()->GetSprite()->Draw(pTextInfo->texture, nullptr,
            &centerVec,
            nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

        return;
    }

    if (!flyState)
    {
        WriteMatrix();

        float fCenterX = info.pos.x * 0.5f;
        float fCenterY = info.pos.y * 0.5f;
        // D3DXVECTOR3 spinCenter{ (info.pos.x * 0.5f), (info.pos.y * 0.5f), 0.f };

        GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

        GraphicDevice::GetInstance()->GetSprite()->Draw(pTextInfo->texture, nullptr,
            &centerVec,
            nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

        //DrawImage(); // �ʼ�!

        // ���� ���̱� üũ(Ű���� L or K)
        if (ObjectManager::GetInstance()->GetShowLineCheck()) {
            // �׷��ȵ���̽��� ����  �ٽ� �׷��� �Ѵ�!
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

        //DrawImage(); // �ʼ�!

        // ���� ���̱� üũ(Ű���� L or K)
        if (ObjectManager::GetInstance()->GetShowLineCheck()) {
            // �׷��ȵ���̽��� ����  �ٽ� �׷��� �Ѵ�!
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
        // ���� ������ Y���� ���� ����
        float fY = 0.f;
        bool lineCheck = CLineMgr::GetInstance()->CollisionLine(info.pos.x, rc.bottom, &fY);

        if (jumpState)
        {
            jumpTime += 0.6f;
            rc.bottom = jumpY - ((jumpPower * jumpTime) - (0.5f * GRAVITIY * jumpTime * jumpTime));
            info.pos.y = rc.bottom - (info.size.y * 0.5f);
            if (lineCheck && rc.bottom >= fY)
            {
                jumpState = false;
                jumpTime = 0.f;
                rc.bottom = fY;
                info.pos.y = rc.bottom - (info.size.y * 0.5f);
            }
        }
        else {
            rc.bottom += GRAVITIY;
            info.pos.y = rc.bottom - (info.size.y * 0.5f);
            fallRotateAngle = true;

            if (rc.bottom >= fY) {
                rc.bottom = fY;
                info.pos.y = rc.bottom - (info.size.y * 0.5f);
                fallRotateAngle = false;
            }

        }
    }
}

void Player::PlaneMovement()
{
    if (fallState == false)
        info.pos.y -= GRAVITIY;
    else
    {
        info.pos.y += GRAVITIY;

        //float fY = 0.f;
        //bool lineCheck = CLineMgr::GetInstance()->CollisionLine(info.pos.x, rc.bottom, &fY);

        //if (lineCheck && info.pos.y >= fY)
        //{
        //    info.pos.y = fY;
        //    m_fAngle = 0;
        //}
    }
}


void Player::KeyChecking()
{
    if (flyState == false)
    {
        if (!jumpState) {
            // Ǯ�� �׽�Ʈ
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
        else if (keyMgr->KeyPressing('W')) {
            ending = true;
            m_fAngle = 0.f;
        }
        else
            fallState = true;
    }
}

void Player::WriteMatrix()
{
    // ũ * �� * �� * �� * �� 
    // ��   ��   ��   ��   ��
    if (flyState == false)
    {
        D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
        //m_fAngle += 5.f;

        D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
        D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, 0.f);

        matWorld = matScale * matRotZ * matTrans;

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
    if (keyMgr->KeyDown(VK_RETURN))
        m_bGod = true;
}

void Player::RotateAngle()
{
    if (flyState == false)
    {// �ӽù���!!
        if (jumpState) {

            m_fAngle += 5.f;

            if (m_fAngle >= 90) {
                m_fAngle = 90;
            }
        }
        else if (fallRotateAngle) {
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
            m_fAngle + 15.f;
            //if (m_fAngle >= 45) {
            //    m_fAngle = 45;
            //}
        }
        else        
            m_fAngle - 15.f;               
    }
}


void Player::SetEffect()
{
    if (jumpState) {
        return;
    }

    if (effectDelay + 100 < GetTickCount64()) {

        D3DXVECTOR3 temp = { info.pos.x - 65.f , info.pos.y + 25.f, 0.f };

        ObjectManager::GetInstance()->InsertObject<RunEffect>(ObjectManager::EFFECT, temp);
        effectDelay = GetTickCount64();
    }
}

void Player::Ending()
{
    D3DXMatrixIdentity(&matWorld);

    m_fAngle += D3DXToRadian(5.f);

    D3DXMATRIX matScale2, matRotate2, matTrans2;
    D3DXMatrixScaling(&matScale2, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotate2, m_fAngle);
    D3DXMatrixTranslation(&matTrans2, info.pos.x += 7.f, info.pos.y, 0.f);

    matWorld = matScale2 * matRotate2 * matTrans2;
}

