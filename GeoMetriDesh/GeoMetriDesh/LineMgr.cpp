#include "framework.h"
#include "LineMgr.h"
#include "Line.h"

IMPLEMENT_SINGLETON(CLineMgr)

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Render()
{
	for (auto& pLine : m_LineList)
		pLine->Render();
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}
