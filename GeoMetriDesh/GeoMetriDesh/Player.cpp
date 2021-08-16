#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"

HRESULT Player::ReadObject()
{
   // �ؽ�Ʈ ������ �߰��ϰ� �ҷ�����
    // �߰�!
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Cube.png", L"Player");
    // �θ���!
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Player");
    // �̹����� ��� �� ������ �����Է�

    // info�� pos, size, dir�� ���� ��������� �Ѵ�
    info.pos = { 100.f, 200.f, 0.f };
    info.size = { 100.f, 100.f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    rgb.A = 255;
    rgb.R = 0;
    rgb.G = 0;
    rgb.B = 255;

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
    DrawImage(); // �ʼ�!
}

void Player::ReleaseObject()
{
    SAFE_DELETE(keyMgr);
}

void Player::KeyChecking()
{
    // Ǯ�� �׽�Ʈ
    if (keyMgr->KeyPressing(VK_SPACE)) {
        SetDeadCheck(true);
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
