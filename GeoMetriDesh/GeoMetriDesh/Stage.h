#pragma once
#include "Scene.h"

class ObjectManager;
class CLineMgr;
class Stage : public Scene
{
private:
    enum COLOR { BLUE, PURPLE, RED, REPURPLE, END };
public:
    // Scene을(를) 통해 상속됨
    virtual HRESULT Initialize() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
    virtual void Release() override;
private:
    void ChangeColor();
private:
    ObjectManager* objMgr;
    CLineMgr* lineMgr;
    
    DWORD dwCurTime;
    DWORD dwSpawnTime;
    COLOR eColor;

    Object* m_pPotal1;
    Object* m_pPotal2;
};

