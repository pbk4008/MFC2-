#pragma once
#ifndef __PLAYBTN_H__
#define __PLAYBTN_H__

#include "Object.h"


class PlayBtn : public Object
{
    // Object��(��) ���� ��ӵ�
    virtual HRESULT ReadObject() override;
    virtual int UpdateObject() override;
    virtual void LateUpdateObject() override;
    virtual void RenderObject() override;
    virtual void ReleaseObject() override;
    void SetMatrix();
};


#endif // !__PLAYBTN_H__