#include "framework.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CScrollMgr)
CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f), m_fUpdateScrollX(0.f), m_fUpdateScrollY(0.f), m_fBackGroundScrollX(0.f), m_fBackSpeed(0.f)
{
}

CScrollMgr::~CScrollMgr()
{

}

void CScrollMgr::XUpdate()
{
	m_fUpdateScrollX += m_fSpeed;
	m_fBackGroundScrollX += m_fBackSpeed;

}

void CScrollMgr::YUpdate()
{
	m_fUpdateScrollY += m_fSpeed;
}

void CScrollMgr::OffSet()
{

}

void CScrollMgr::setScrollY(float _scrolly)
{
	m_fScrollY = _scrolly;
	/*
	while (_scrolly != m_fScrollY)
	{
		m_fScrollY += 10.f;
	}*/
}
