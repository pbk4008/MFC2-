#pragma once
#include "Object.h"
class CScrollMgr;
class CLand :
    public Object
{
private:
    const int LANDCX = 65;
    const int LANDCY = 81;
private:
    float m_fLandDist;
    D3DXVECTOR2 m_fLandStart;
    D3DXVECTOR2 m_fLandEnd;
    LPD3DXSPRITE m_pSprite;

    CScrollMgr* m_pScrollMgr;
private:
    explicit CLand();
public:
    virtual ~CLand();
public:
    // Object을(를) 통해 상속됨
    virtual HRESULT ReadObject() override;
    virtual int UpdateObject() override;
    virtual void LateUpdateObject() override;
    virtual void RenderObject() override;
    virtual void ReleaseObject() override;
public:
    static Object* Create();
};

