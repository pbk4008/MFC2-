#include "framework.h"
#include "Player.h"
#include "GraphicDevice.h"

HRESULT Player::ReadObject()
{
    info.pos = { 300, 300, 0.f};

    return S_OK;
}

int Player::UpdateObject()
{
    return 0;
}

void Player::LateUpdateObject()
{
}

void Player::RenderObject(HDC _hdc)
{
}

void Player::ReleaseObject()
{
}
