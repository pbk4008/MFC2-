#include "framework.h"
#include "ObjectManager.h"
#include "Object.h"

void Object::SetObjectInfo()
{
    // �̹��� ����!
    centerVec = { pTextInfo->imageInfo.Width * 0.5f, pTextInfo->imageInfo.Height * 0.5f, 0.f };
}

void Object::UpdateObjectInfo()
{
    // ��Ʈ �� �׸���!
    // �׸��� ���� �߿���
    D3DXVECTOR2 leftTop = { {info.pos.x - centerVec.x}, {info.pos.y - centerVec.y} };
    D3DXVECTOR2 rightTop = { {info.pos.x + centerVec.x}, {info.pos.y - centerVec.y} };
    D3DXVECTOR2 rightBottom = { {info.pos.x + centerVec.x }, {info.pos.y + centerVec.y} };
    D3DXVECTOR2 leftBottom = { {info.pos.x - centerVec.x }, {info.pos.y + centerVec.y} };

    lineList[0] = { leftTop.x, leftTop.y };
    lineList[1] = { rightTop.x, rightTop.y };
    lineList[2] = { rightBottom.x, rightBottom.y };
    lineList[3] = { leftBottom.x, leftBottom.y };
    lineList[4] = { leftTop.x, leftTop.y };
    // ���θ���Ʈ 5������ ������ü �� �׷���

    // �浹ó���� RECT �� ����
    rc.left = (LONG)leftTop.x - (LONG)(info.size.x * 0.5f);
    rc.right = (LONG)leftTop.x + (LONG)(info.size.x * 0.5f);
    rc.top = (LONG)leftTop.y - (LONG)(info.size.y * 0.5f);
    rc.bottom = (LONG)leftTop.y + (LONG)(info.size.y * 0.5f);
}

void Object::DrawImage()
{
    // �׸��׸���
    GraphicDevice::GetInstance()->GetSprite()->Draw(pTextInfo->texture, nullptr,
        &centerVec,
        &info.pos, D3DCOLOR_ARGB(255, 255, 255, 255));

    // ���� ���̱� üũ(Ű���� L or K)
    if (ObjectManager::GetInstance()->GetShowLineCheck()) {
        // �׷��ȵ���̽��� ����  �ٽ� �׷��� �Ѵ�!
        GraphicDevice::GetInstance()->GetSprite()->End();
        GraphicDevice::GetInstance()->GetLine()->SetWidth(3.f);
        GraphicDevice::GetInstance()->GetLine()->Draw(lineList, 5, D3DCOLOR_ARGB(255, 255, 0, 0));
        GraphicDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
    }
}
