#pragma once
#include "Object.h"
class CPotal :
    public Object
{
public:
    // Object을(를) 통해 상속됨
    virtual HRESULT ReadObject() override;
    virtual int UpdateObject() override;
    virtual void LateUpdateObject() override;
    virtual void RenderObject() override;
    virtual void ReleaseObject() override;
public:
    int iIndex;
    float posX;
};

