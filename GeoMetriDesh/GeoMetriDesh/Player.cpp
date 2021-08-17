#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"

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
    // �̹����� ��� �� ������ �����Է�

    // info�� pos, size, dir�� ���� ��������� �Ѵ�
    info.pos = { 100.f, 100.f, 0.f }; //xyz
    info.size = { 100.f, 100.f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    // �ݺ� ������ ���̱� ���� ����!
    keyMgr = KeyManager::GetInstance();

    SetObjectInfo(); // �ʼ�!
    return S_OK;
}

int Player::UpdateObject()
{
    KeyChecking();
    
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
}

void Player::ReleaseObject()
{
    SAFE_DELETE(keyMgr);
}

void Player::KeyChecking()
{
    // Ǯ�� �׽�Ʈ
    if (keyMgr->KeyPressing(VK_SPACE)) {
        int iCount = 0;
        for (0; iCount <= 18; ++iCount)
        {
            m_fAngle += 5.f;
        }
        iCount = 0;
       // SetDeadCheck(true);
    };
    if (keyMgr->KeyPressing('W')) {
        SetDeadCheck(false);
    };

    // Ű �׽�Ʈ
    if (keyMgr->KeyPressing(VK_LEFT)) {
        info.pos.x -= 5.f;
    }
    if (keyMgr->KeyPressing(VK_RIGHT)) {
        info.pos.x += 5.f;
    }
    if (keyMgr->KeyPressing(VK_UP)) {
        info.pos.y -= 5.f;
    }
    if (keyMgr->KeyPressing(VK_DOWN)) {
        info.pos.y += 5.f;
    }

}

void Player::WriteMatrix()
{
    // ũ * �� * �� * �� * �� 
    // ��   ��   ��   ��   ��
    
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
    //m_fAngle += 5.f;

    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);

    matWorld = matScale * matRotZ * matTrans;



    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
}
