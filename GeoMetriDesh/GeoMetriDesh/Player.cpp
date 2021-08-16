#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"

HRESULT Player::ReadObject()
{
   // 텍스트 정보를 추가하고 불러야함
    // 추가!
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Cube.png", L"Player");
    // 부르기!
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Player");
    // 이미지들 경로 및 정보를 수기입력

    // info의 pos, size, dir는 직접 지정해줘야 한다
    info.pos = { 100.f, 200.f, 0.f };
    info.size = { 100.f, 100.f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };

    rgb.A = 255;
    rgb.R = 0;
    rgb.G = 0;
    rgb.B = 255;

    // 반복 연산을 줄이기 위해 선언!
    keyMgr = KeyManager::GetInstance();

    SetObjectInfo(); // 필수!
    return S_OK;
}

int Player::UpdateObject()
{
    KeyChecking();
    return NOEVENT;
}

void Player::LateUpdateObject()
{
    UpdateObjectInfo(); // 필수!
}

void Player::RenderObject()
{
    DrawImage(); // 필수!
}

void Player::ReleaseObject()
{
    SAFE_DELETE(keyMgr);
}

void Player::KeyChecking()
{
    // 풀링 테스트
    if (keyMgr->KeyPressing(VK_SPACE)) {
        SetDeadCheck(true);
    };
    if (keyMgr->KeyPressing('W')) {
        SetDeadCheck(false);
    };

    // 키 테스트
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
