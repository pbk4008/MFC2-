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
	float m_fSpeed;
private:
	CScrollMgr();
	~CScrollMgr();
public:
	void XUpdate();
	void YUpdate();
public:
	inline void setScrollX(float _scrollx) { m_fScrollX += _scrollx; }
	inline void setScrollY(float _scrolly) { m_fScrollY += _scrolly; }
	inline void setSpeed(float _speed) { m_fSpeed = _speed; }
	inline void reSetSpeed() { m_fSpeed = 0.f; }
public:
	inline float getScrollX() { return m_fScrollX; }
	inline float getScrollY() { return m_fScrollY; }
	inline float getUpdateScrollX() { return m_fUpdateScrollX; }
	inline float getUpdateScrollY() { return m_fUpdateScrollY; }
	inline float getSpeed() { return m_fSpeed; }
};
#endif

