#pragma once
#include "Scene.h"

class ObjectManager;
class CLineMgr;
class Stage : public Scene
{
    // Scene��(��) ���� ��ӵ�
    virtual HRESULT Initialize() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
    virtual void Release() override;
private:
    ObjectManager* objMgr;
    CLineMgr* lineMgr;
};

