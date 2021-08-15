#include "framework.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
{
	ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
}

CLine::~CLine()
{
	Release();
}

void CLine::Render()
{
	float fScrollX = CScrollMgr::GetInstance()->getScrollX();
	float fScrollY = CScrollMgr::GetInstance()->getScrollY();

	D3DXVECTOR2 argLinePos[2] = { {m_tLinePos[0].x - fScrollX, m_tLinePos[0].y - fScrollY},
		{m_tLinePos[1].x - fScrollX, m_tLinePos[1].y - fScrollY} };
	
	m_pLine->SetWidth(3.f);
	m_pLine->Draw(argLinePos, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
}

void CLine::Release()
{
}

CLine* CLine::Create(const D3DXVECTOR3& _lPos, const D3DXVECTOR3& _rPos)
{
	CLine* pInstance = new CLine();
	if (FAILED(pInstance->setLineInfo(_lPos, _rPos)))
		SAFE_DELETE(pInstance);
	return pInstance;
}

CLine* CLine::Create(const D3DXVECTOR2& _lPos, const D3DXVECTOR2& _rPos)
{
	CLine* pInstance = new CLine();
	if (FAILED(pInstance->setLineInfo(_lPos, _rPos)))
		SAFE_DELETE(pInstance);
	return pInstance;
}

HRESULT CLine::setLineInfo(const D3DXVECTOR3& _lPos, const D3DXVECTOR3& _rPos)
{
	m_tLinePos[0] = D3DXVECTOR2(_lPos.x,_lPos.y);
	m_tLinePos[1] = D3DXVECTOR2(_rPos.x,_rPos.y);
	m_pLine = GraphicDevice::GetInstance()->GetLine();
	return S_OK;
}

HRESULT CLine::setLineInfo(const D3DXVECTOR2& _lPos, const D3DXVECTOR2& _rPos)
{
	m_tLinePos[0] = _lPos;
	m_tLinePos[1] = _rPos;
	m_pLine = GraphicDevice::GetInstance()->GetLine();
	return S_OK;
}
