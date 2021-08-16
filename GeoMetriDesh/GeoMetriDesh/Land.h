#pragma once
#include "Object.h"
class CLand :
    public Object
{
private:
    const int LANDCX = 81;
    const int LANDCY = 81;
private:
    float m_fLandDist;
private:
    explicit CLand();
public:
    virtual ~CLand();
public:
    // Object��(��) ���� ��ӵ�
    virtual HRESULT ReadObject() override;
    virtual int UpdateObject() override;
    virtual void LateUpdateObject() override;
    virtual void RenderObject() override;
    virtual void ReleaseObject() override;
};

