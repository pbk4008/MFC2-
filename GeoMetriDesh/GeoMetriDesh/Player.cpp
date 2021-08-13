#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"
#include "TextureManager.h"
#include "KeyManager.h"

HRESULT Player::ReadObject()
{
    test = 1;
    TextureManager::GetInstance()->InsertTexture(TextureManager::MULTI, L"../Texture/Stage/Player/Attack/AKIHA_AKI01_00%d.png", L"Player", L"Attack", 6);

    info.pos = { 400, 100, 0.f };

    return S_OK;
}

int Player::UpdateObject()
{
    
    if (KeyManager::GetInstance()->KeyPressing(VK_SPACE)) {
        SetDeadCheck(true);
    };


    if (KeyManager::GetInstance()->KeyPressing('W')) {
        SetDeadCheck(false);
    };

    test++;
    return NOEVENT;
}

void Player::LateUpdateObject()
{
    if (test >= 6) {
        test = 0;
    }

}

void Player::RenderObject()
{
    const TEXTINFO* pTexInfo = TextureManager::GetInstance()->GetTextInfo(L"Player", L"Attack", test);

    float centerX = (float)(pTexInfo->imageInfo.Width >> 1);
    float centerY = (float)(pTexInfo->imageInfo.Height >> 1);

    D3DXVECTOR3 temp = { centerX, centerY, 0.f};


    GraphicDevice::GetInstance()->GetSprite()->Draw(pTexInfo->texture, nullptr,&temp,&info.pos, D3DCOLOR_ARGB(255,255,255,255));
}

void Player::ReleaseObject()
{
}
