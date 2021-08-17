#include "framework.h"
#include "SubObject.h"
#include "TextureManager.h"

HRESULT SubObject::ReadObject()
{
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Cube.png", L"Player");
    // ºÎ¸£±â!
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Player");

    info.pos = { 500.f, 200.f, 0.f };
    info.size = { 100.f, 100.f, 0.f };
    info.dir = { 1.f, 0.f, 0.f };


    SetObjectInfo();
    return S_OK;
}

int SubObject::UpdateObject()
{
    return NOEVENT;
}

void SubObject::LateUpdateObject()
{
    UpdateObjectInfo();
}

void SubObject::RenderObject()
{
    DrawImage();
}

void SubObject::ReleaseObject()
{
}
