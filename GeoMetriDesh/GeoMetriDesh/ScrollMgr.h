#pragma once
#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__
class CScrollMgr
{
DECLARE_SINGLETON(CScrollMgr)
private:
	float m_fScrollX;
	float m_fScrollY;
	float m_fUpdateScrollX;
	float m_fUpdateScrollY;
	float m_fBackGroundScrollX;
	float m_fSpeed;
	float m_fBackSpeed;
private:
	CScrollMgr();
	~CScrollMgr();
public:
	void XUpdate();
	void YUpdate();
	void OffSet();
	void setScrollY(float _scrolly);
public:
	inline void setScrollX(float _scrollx) { m_fScrollX += _scrollx; }
	inline void setSpeed(float _speed) { m_fSpeed = _speed; }
	inline void setBackSpeed(float _speed) { m_fBackSpeed = _speed; }
	inline void reSetSpeed() { m_fSpeed = 0.f; }
	inline void reSetBackSpeed() { m_fBackSpeed = 0.f; }
	inline void setBackGroundScrollX(float _scrollx) { m_fBackGroundScrollX = _scrollx; }
	inline void setUpdateScrollX(float _scrollx) { m_fUpdateScrollX = _scrollx; }

public:
	inline float getScrollX() { return m_fScrollX; }
	inline float getScrollY() { return m_fScrollY; }
	inline float getUpdateScrollX() { return m_fUpdateScrollX; }
	inline float getUpdateScrollY() { return m_fUpdateScrollY; }
	inline float getSpeed() { return m_fSpeed; }
	inline float getBackGroundScrollX() { return m_fBackGroundScrollX; };
	inline float getBackSpeed() { return m_fBackSpeed; };
};
#endif

