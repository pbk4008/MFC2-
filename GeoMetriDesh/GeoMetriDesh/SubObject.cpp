#include "framework.h"
#include "SubObject.h"
#include "TextureManager.h"

HRESULT SubObject::ReadObject()
{
    // �ؽ�Ʈ ������ �߰��ϰ� �ҷ�����
     // �߰�!
    TextureManager::GetInstance()->InsertTexture(TextureManager::SINGLE, L"../Texture/Logo.jpg", L"Sub");
    // �θ���!
    pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Sub");
    // �̹����� ��� �� ������ �����Է�

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
    WriteMatrix();
    DrawImage();
}

void SubObject::ReleaseObject()
{
}

void SubObject::WriteMatrix()
{
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);

    GraphicDevice::GetInstance()->GetSprite()->SetTransform(&matScale);

}
