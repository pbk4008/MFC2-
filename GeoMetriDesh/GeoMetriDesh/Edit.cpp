#include "framework.h"
#include "Edit.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "Line.h"

CEdit::CEdit() : m_pScrollMgr(nullptr),m_pSprite(nullptr),m_pTextureMgr(nullptr), m_pKeyMgr(nullptr), m_pLineMgr(nullptr),
m_bTile(false), m_bFirst(false),
m_iIndex(0)
{
	ZeroMemory(&m_tMouse, sizeof(POINT));
	ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
}

CEdit::~CEdit()
{
}

HRESULT CEdit::Initialize()
{
	m_pSprite = GraphicDevice::GetInstance()->GetSprite();
	m_pTextureMgr = TextureManager::GetInstance();
	m_pKeyMgr = KeyManager::GetInstance();
	m_pLineMgr = CLineMgr::GetInstance();
	m_pScrollMgr = CScrollMgr::GetInstance();

	m_pTextureMgr->InsertTexture(TextureManager::MULTI, L"../Texture/Obstacle/Obstacle00%d.png", L"Tile", L"Obstacle", 6);
	return S_OK;
}

int CEdit::Update()
{
	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);
	if (m_pKeyMgr->KeyDown('1'))
		m_bTile = false;
	if (m_pKeyMgr->KeyDown('2'))
		m_bTile = true;

	if (m_pKeyMgr->KeyPressing(VK_RIGHT))
		m_pScrollMgr->setScrollX(5.f);
	if(m_pKeyMgr->KeyPressing(VK_LEFT))
		m_pScrollMgr->setScrollX(-5.f);

	if (m_pKeyMgr->KeyDown('S'))
		m_pLineMgr->SaveLine();
	if (m_pKeyMgr->KeyDown('A'))
		m_pLineMgr->LoadLine();

	if (m_bTile)
		CreateTile();
	else
		CreateLine();
	
	return 0;
}

void CEdit::LateUpdate()
{
	if (m_iIndex < 0)
		m_iIndex = 0;
	if (m_iIndex > 5)
		m_iIndex = 5;
}

void CEdit::Render()
{
	if (m_bTile)
	{
		const TEXTINFO* pTexture = m_pTextureMgr->GetTextInfo(L"Tile", L"Obstacle", m_iIndex);

		float fCenterX = float(pTexture->imageInfo.Width >> 1);
		float fCenterY = float(pTexture->imageInfo.Height >> 1);

		D3DXVECTOR3 vecCenter{ fCenterX, fCenterY, 0.f };
		D3DXVECTOR3 vecMouse{ float(m_tMouse.x), float(m_tMouse.y), 0.f };
		m_pSprite->Draw(pTexture->texture, nullptr, &vecCenter, &vecMouse, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	m_pLineMgr->Render();
}

void CEdit::Release()
{
}

void CEdit::CreateTile()
{
	if (m_bTile)
	{
		if (m_pKeyMgr->KeyDown(VK_UP))
			m_iIndex++;

		if (m_pKeyMgr->KeyDown(VK_DOWN))
			m_iIndex--;
	}
}

void CEdit::CreateLine()
{
	float fScrollX = m_pScrollMgr->getScrollX();
	float fScrollY = m_pScrollMgr->getScrollY();
	if (m_pKeyMgr->KeyDown(VK_LBUTTON))
	{
		if (m_bFirst)
		{
			if (m_pKeyMgr->KeyPressing(VK_SHIFT))
				m_tLinePos[1] = { float(m_tMouse.x+ fScrollX), m_tLinePos[0].y,0.f };
			else
				m_tLinePos[1] = { float(m_tMouse.x+ fScrollX), float(m_tMouse.y+ fScrollY), 0.f };
			
			CLine* pLine = CLine::Create(m_tLinePos[0], m_tLinePos[1]);
			m_pLineMgr->AddLine(pLine);
			memcpy(m_tLinePos[0], m_tLinePos[1], sizeof(D3DXVECTOR3));
		}
		else
		{
			m_tLinePos[0] = { float(m_tMouse.x+ fScrollX), float(m_tMouse.y+ fScrollY), 0.f };
			m_bFirst = true;
		}

	}
	if (m_pKeyMgr->KeyDown(VK_RBUTTON))
	{
		ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
		m_bFirst = false;
	}
}

