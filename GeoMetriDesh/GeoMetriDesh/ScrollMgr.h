#pragma once
#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__
class CScrollMgr
{
DECLARE_SINGLETON(CScrollMgr)
private:
	float m_fScrollX;
	float m_fScrollY;
private:
	CScrollMgr();
	~CScrollMgr();
public:
	inline void setScrollX(float _scrollx) { m_fScrollX += _scrollx; }
	inline void setScrollY(float _scrolly) { m_fScrollY += _scrolly; }
public:
	inline float getScrollX() { return m_fScrollX; }
	inline float getScrollY() { return m_fScrollY; }
};
#endif

