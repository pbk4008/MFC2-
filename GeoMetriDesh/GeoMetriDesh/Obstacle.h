#pragma once
#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
#include "Object.h"
class CObstacle :
    public Object
{
private:
    OBSTACLEINFO m_tObstalceInfo;
    LPD3DXSPRITE m_pSprite;
public:
    explicit CObstacle();
    virtual ~CObstacle();
public:
    virtual HRESULT ReadObject() override;
    virtual int UpdateObject() override;
    virtual void LateUpdateObject() override;
    virtual void RenderObject() override;
    virtual void ReleaseObject() override;
public:
    void Respawn(const int _iIndex, const D3DXMATRIX& _matrix);
public:
    inline void setIndex(const int _iIndex) { m_tObstalceInfo.iIndex = _iIndex; }
    inline void setMatrix(const D3DXMATRIX& _matrix) { m_tObstalceInfo.tMatrix = _matrix; }
    inline void setColor(const RGBINFO& _rInfo) { rgb = _rInfo; }
public:
    inline const OBSTACLEINFO& const getObstacleInfo() { return m_tObstalceInfo; }
};
#endif

