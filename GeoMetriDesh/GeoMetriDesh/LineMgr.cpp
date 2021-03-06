#include "framework.h"
#include "LineMgr.h"
#include "Line.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CLineMgr)

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Update()
{
	for (auto& pLine : m_LineList)
		pLine->Update();
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

void CLineMgr::SaveLine()
{
	HANDLE hfile = CreateFile(L"../Data/Line.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hfile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"저장 실패", L"실패", MB_OK);
		return;
	}
	DWORD dwByte = 0;

	for (auto& pLine : m_LineList)
	{
		WriteFile(hfile, pLine->getPos(), sizeof(D3DXVECTOR2)*2, &dwByte, nullptr);
	}
	MessageBox(g_hWnd, L"저장 성공", L"성공", MB_OK);
	CloseHandle(hfile);
}

void CLineMgr::LoadLine()
{
	HANDLE hfile = CreateFile(L"../Data/Line.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hfile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"로드 실패", L"실패", MB_OK);
		return;
	}
	Release();
	DWORD dwByte = 0;
	D3DXVECTOR2 argVec[2] = {};
	while(true)
	{
		ReadFile(hfile, argVec, sizeof(argVec), &dwByte, nullptr);
		if (dwByte == 0)
			break;
		AddLine(CLine::Create(argVec[0], argVec[1]));
	}
	/*MessageBox(g_hWnd, L"로드 성공", L"성공", MB_OK);*/
	CloseHandle(hfile);
}

void CLineMgr::DeleteLine()
{
	Safe_Delete(m_LineList.back());
	m_LineList.pop_back();
}

float CLineMgr::getLineDist(D3DXVECTOR2& _start, D3DXVECTOR2& _end)
{
	float argDist=0.f;
	D3DXVECTOR2 min = {};
	D3DXVECTOR2 tmp;
	ZeroMemory(&tmp, sizeof(D3DXVECTOR2));
	ZeroMemory(&min, sizeof(D3DXVECTOR2));
	for (auto& pLine : m_LineList)
	{
		if (0==D3DXVec2Length(&tmp))
		{
			min = pLine->getPos()[0];
			tmp = pLine->getPos()[1];
			continue;
		}
		if (tmp != pLine->getPos()[0])
			break;
	}
	_start = min;
	_end = tmp;
	D3DXVECTOR2 DistVec = tmp - min;
	float fDist = D3DXVec2Length(&DistVec);
	return fDist;
}



bool CLineMgr::CollisionLine(float _infoX, float _infoY, float* _Y)
{
	float scrollX = CScrollMgr::GetInstance()->getUpdateScrollX();
	float scrollY = CScrollMgr::GetInstance()->getScrollY();

	if (m_LineList.empty()) {
		return false;
	}

	// x 탐색
	float min = WINCY;
	float ny;
	float dist;
	for (auto& rLine : m_LineList) {
		if (rLine->getPos()[0].x - scrollX <= _infoX &&
			rLine->getPos()[1].x - scrollX > _infoX)
		{
			float	x1 = rLine->getPos()[0].x - scrollX;
			float	y1 = rLine->getPos()[0].y - scrollY;
			float	x2 = rLine->getPos()[1].x - scrollX;
			float	y2 = rLine->getPos()[1].y - scrollY;

			// 딯을 땅이고
			ny = ((y2 - y1) / (x2 - x1)) * (_infoX - x1) + y1;

			if (ny >= _infoY) {
				dist = ny - _infoY;

				if (min > dist) {
					min = dist;
					*_Y = ny;
					int i = 0;
				}
			}
		}
	}
	return true;
}
