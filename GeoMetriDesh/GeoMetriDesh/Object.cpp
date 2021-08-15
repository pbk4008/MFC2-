#include "framework.h"
#include "ObjectManager.h"
#include "Object.h"

void Object::SetObjectInfo()
{
    // 이미지 센터!
    centerVec = { pTextInfo->imageInfo.Width * 0.5f, pTextInfo->imageInfo.Height * 0.5f, 0.f };
}

void Object::UpdateObjectInfo()
{
    // 렉트 선 그리기!
    // 그리는 순서 중요함
    D3DXVECTOR2 leftTop = { {info.pos.x - centerVec.x}, {info.pos.y - centerVec.y} };
    D3DXVECTOR2 rightTop = { {info.pos.x + centerVec.x}, {info.pos.y - centerVec.y} };
    D3DXVECTOR2 rightBottom = { {info.pos.x + centerVec.x }, {info.pos.y + centerVec.y} };
    D3DXVECTOR2 leftBottom = { {info.pos.x - centerVec.x }, {info.pos.y + centerVec.y} };

    lineList[0] = { leftTop.x, leftTop.y };
    lineList[1] = { rightTop.x, rightTop.y };
    lineList[2] = { rightBottom.x, rightBottom.y };
    lineList[3] = { leftBottom.x, leftBottom.y };
    lineList[4] = { leftTop.x, leftTop.y };
    // 라인리스트 5개여야 정육면체 다 그려짐

    // 충돌처리할 RECT 값 구성
    rc.left = (LONG)leftTop.x - (LONG)(info.size.x * 0.5f);
    rc.right = (LONG)leftTop.x + (LONG)(info.size.x * 0.5f);
    rc.top = (LONG)leftTop.y - (LONG)(info.size.y * 0.5f);
    rc.bottom = (LONG)leftTop.y + (LONG)(info.size.y * 0.5f);
}

void Object::DrawImage()
{
    // 그림그리기
    GraphicDevice::GetInstance()->GetSprite()->Draw(pTextInfo->texture, nullptr,
        &centerVec,
        &info.pos, D3DCOLOR_ARGB(255, 255, 255, 255));

    // 라인 보이기 체크(키보드 L or K)
    if (ObjectManager::GetInstance()->GetShowLineCheck()) {
        // 그래픽디바이스를 끄고  다시 그려야 한다!
        GraphicDevice::GetInstance()->GetSprite()->End();
        GraphicDevice::GetInstance()->GetLine()->SetWidth(3.f);
        GraphicDevice::GetInstance()->GetLine()->Draw(lineList, 5, D3DCOLOR_ARGB(255, 255, 0, 0));
        GraphicDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
    }
}
