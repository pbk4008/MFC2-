#pragma once
#include "Scene.h"
class TextureManager;
class KeyManager;
class CEdit :
    public Scene
{
private:
    explicit CEdit();
public:
    virtual ~CEdit();
public:
    // Scene을(를) 통해 상속됨
    virtual HRESULT Initialize() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
    virtual void Release() override;
public:
    static Scene* Create();
private:
    POINT m_tMouse;
    TextureManager* m_pTextureMgr;
    KeyManager* m_pKeyMgr;
    LPD3DXSPRITE m_pSprite;
    int m_iIndex;
};

