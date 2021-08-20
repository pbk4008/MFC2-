#pragma once
#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
class CScrollMgr;
#include "Object.h"
class CObstacle :
    public Object
{
private:
    const static int OBSTACLECX = 40;
    const static int OBSTACLECY = 40;
private:
    OBSTACLEINFO m_tObstacleInfo;
    LPD3DXSPRITE m_pSprite;
    CScrollMgr* m_pScrollMgr;
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
    void Respawn(const OBSTACLEINFO& _Info);
    void Respawn(const int& _iIndex, const D3DMATRIX& _matMatrix);
public:
    inline void setIndex(const int _iIndex) { m_tObstacleInfo.iIndex = _iIndex; }
    inline void setMatrix(const D3DXMATRIX& _matrix) { m_tObstacleInfo.tMatrix = _matrix; }
    inline void setColor(const RGBINFO& _rInfo) { rgb = _rInfo; }
    inline void setInfo(const OBSTACLEINFO& _Info) { memcpy(&m_tObstacleInfo, &_Info, sizeof(OBSTACLEINFO)); }
public:
    inline const OBSTACLEINFO& const getObstacleInfo() { return m_tObstacleInfo; }
};
#endif

