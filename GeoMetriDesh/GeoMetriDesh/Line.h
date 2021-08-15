#pragma once
#ifndef __LINE_H__
#define __LINE_H__
class CLine
{
private:
	D3DXVECTOR2 m_tLinePos[2];
	LPD3DXLINE m_pLine;
private:
	CLine();
public:
	~CLine();
public:
	void Render();
	void Release();

public:
	static CLine* Create(const D3DXVECTOR3& _lPos, const D3DXVECTOR3& _rPos);
private:
	HRESULT setLineInfo(const D3DXVECTOR3& _lPos, const D3DXVECTOR3& _rPos);
};
#endif

