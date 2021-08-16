#pragma once
#include "Scene.h"
class TextureManager;
class KeyManager;
class CLineMgr;
class CScrollMgr;
class ObjectManager;
class Object;
class CEdit :
    public Scene
{
private:
    POINT m_tMouse;
    TextureManager* m_pTextureMgr;
    KeyManager* m_pKeyMgr;
    CLineMgr* m_pLineMgr;
    ObjectManager* m_pObjMgr;
    CScrollMgr* m_pScrollMgr;
    LPD3DXSPRITE m_pSprite;
    D3DXVECTOR3 m_tLinePos[2];
    int m_iIndex;
    bool m_bTile;//타일그릴건지 라인 그릴건지 판단
    bool m_bFirst;

    Object* m_pLand;


    D3DXMATRIX m_matWorld;
    float m_fSize;
    float m_fAngle;
public:
    explicit CEdit();
    virtual ~CEdit();
public:
    // Scene을(를) 통해 상속됨
    virtual HRESULT Initialize() override;
    virtual int Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;
    virtual void Release() override;
private:
    void CreateTile();
    void CreateLine();

};

