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
