#pragma once
#ifndef __LINEMGR_H__
#define __LINEMGR_H__
class CLine;
class CLineMgr
{
DECLARE_SINGLETON(CLineMgr)
private:
	list<CLine*> m_LineList;
private:
	CLineMgr();
	~CLineMgr();
public:
	void Update();
	void Render();
	void Release();
public:
	void SaveLine();
	void LoadLine();
	void DeleteLine();
	float getLineDist(D3DXVECTOR2& _start, D3DXVECTOR2& _end);
public:
	inline void AddLine(CLine* _Line) { m_LineList.emplace_back(_Line); }
	bool CollisionLine(float _infoX, float _infoY, float* _Y);
};
#endif

