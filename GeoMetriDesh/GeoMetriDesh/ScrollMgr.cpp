#include "framework.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CScrollMgr)
CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f),m_fUpdateScrollX(0.f),m_fUpdateScrollY(0.f)
{
}

CScrollMgr::~CScrollMgr()
{

}

void CScrollMgr::XUpdate()
{
	m_fUpdateScrollX += m_fSpeed;
}

void CScrollMgr::YUpdate()
{
	m_fUpdateScrollY += m_fSpeed;
}
