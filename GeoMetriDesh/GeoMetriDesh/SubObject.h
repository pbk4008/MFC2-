#pragma once
#include "Object.h"
#ifndef __SUB_OBJECT_H__
#define __SUB_OBJECT_H__

class SubObject : public Object
{
    // Object��(��) ���� ��ӵ�
    virtual HRESULT ReadObject() override;
    virtual int UpdateObject() override;
    virtual void LateUpdateObject() override;
    virtual void RenderObject() override;
    virtual void ReleaseObject() override;

public:
    void WriteMatrix();

private:
    D3DXMATRIX	matScale;
};


#endif // !__SUB_OBJECT_H__