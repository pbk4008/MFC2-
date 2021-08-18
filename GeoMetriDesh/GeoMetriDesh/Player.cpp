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
   // �ؽ�Ʈ ������ �߰��ϰ� �ҷ�����
    // �߰�!
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Player.png", L"Player");
    // �θ���!
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Player");

    // info�� pos, size, dir�� ���� ��������� �Ѵ�
    info.pos = { 300.f, 100.f, 0.f }; //xyz
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

    jumpState = true;
    jumpTime = 100.f;
    jumpPower = 70.f;
    jumpY = 0;


    SetObjectInfo(); // �ʼ�!
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

    UpdateObjectInfo(); // �ʼ�!
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

void Player::ReleaseObject()
{
    SAFE_DELETE(keyMgr);
}

void Player::Jumping()
{
    if (!jumpState) {
        return;
    }

    // ���� ������ Y���� ���� ����
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
        // Ǯ�� �׽�Ʈ
        if (keyMgr->KeyDown(VK_SPACE)) {
           
            jumpY = info.pos.y;
            jumpState = true;
        };
    }
    //if (keyMgr->KeyPressing('W')) {
    //    SetDeadCheck(false);
    //};

    //// Ű �׽�Ʈ
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
    // ũ * �� * �� * �� * �� 
    // ��   ��   ��   ��   ��
    
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
    //m_fAngle += 5.f;

    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, info.pos.x, info.pos.y, 0.f);

    matWorld = matScale * matRotZ * matTrans;



    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
}

void Player::RotateAngle()
{
    // �ӽù���!!
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
