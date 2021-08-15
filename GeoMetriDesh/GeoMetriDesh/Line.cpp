#include "framework.h"
#include "Line.h"

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
	m_pLine->SetWidth(3.f);
	m_pLine->Draw(m_tLinePos, 2, D3DCOLOR_ARGB(255, 255, 0, 0));
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

HRESULT CLine::setLineInfo(const D3DXVECTOR3& _lPos, const D3DXVECTOR3& _rPos)
{
	m_tLinePos[0] = D3DXVECTOR2(_lPos.x,_lPos.y);
	m_tLinePos[1] = D3DXVECTOR2(_rPos.x,_rPos.y);
	m_pLine = GraphicDevice::GetInstance()->GetLine();
	return S_OK;
}
