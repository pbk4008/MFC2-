#include "framework.h"
#include "Edit.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "ScrollMgr.h"
#include "ObjectManager.h"
#include "LineMgr.h"
#include "Line.h"
#include "Land.h"
#include "Obstacle.h"

CEdit::CEdit() : m_pLand(nullptr), m_pObjMgr(nullptr), m_pScrollMgr(nullptr),m_pSprite(nullptr),m_pTextureMgr(nullptr), m_pKeyMgr(nullptr), m_pLineMgr(nullptr),
m_bTile(false), m_bFirst(false),
m_iIndex(0)
{
	ZeroMemory(&m_tMouse, sizeof(POINT));
	ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
	ZeroMemory(&m_matWorld, sizeof(D3DXMATRIX));
}

CEdit::~CEdit()
{
	Release();
}

HRESULT CEdit::Initialize()
{
	m_pSprite = GraphicDevice::GetInstance()->GetSprite();
	m_pTextureMgr = TextureManager::GetInstance();
	m_pKeyMgr = KeyManager::GetInstance();
	m_pLineMgr = CLineMgr::GetInstance();
	m_pScrollMgr = CScrollMgr::GetInstance();
	m_pObjMgr = ObjectManager::GetInstance();
	m_pLineMgr->LoadLine();

	m_pTextureMgr->InsertTexture(TextureManager::MULTI, L"../Texture/Obstacle/Obstacle00%d.png", L"Tile", L"Obstacle", 6);
	
	m_pLand = new CLand();
	m_pLand->ReadObject();

	m_fSize = 1.f;
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

	/*if (m_pKeyMgr->KeyDown('S'))
		m_pLineMgr->SaveLine();*/
	/*if (m_pKeyMgr->KeyDown('A'))
		m_pLineMgr->LoadLine();*/

	if (m_pKeyMgr->KeyDown('K'))
		m_pObjMgr->SaveObject();

	if (m_bTile)
		CreateTile();
	else
		CreateLine();

	m_pLand->UpdateObject();
	
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
		m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(pTexture->texture, nullptr, &vecCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	m_pLineMgr->Render();
	m_pObjMgr->Render();
	//m_pLand->RenderObject();
}

void CEdit::Release()
{
	Safe_Delete(m_pLand);
}

void CEdit::CreateTile()
{
	if (m_pKeyMgr->KeyDown(VK_UP))
		m_iIndex++;
	if (m_pKeyMgr->KeyDown(VK_DOWN))
		m_iIndex--;

	if (m_pKeyMgr->KeyPressing(VK_ADD))
		m_fSize+=0.1f;
	if (m_pKeyMgr->KeyPressing(VK_SUBTRACT))
		m_fSize -= 0.1f;
	if (m_pKeyMgr->KeyDown(VK_NUMPAD0))
		m_fAngle = D3DXToRadian(0.f);



	if (m_pKeyMgr->KeyPressing(VK_CONTROL))
	{
		if (m_pKeyMgr->KeyDown(VK_NUMPAD4))
			m_fAngle -= D3DXToRadian(90.f);
		if (m_pKeyMgr->KeyDown(VK_NUMPAD6))
			m_fAngle += D3DXToRadian(90.f);
	}

	if (m_pKeyMgr->KeyPressing(VK_NUMPAD4))
	{
		if(!m_pKeyMgr->KeyPressing(VK_CONTROL))
			m_fAngle -= D3DXToRadian(5.f);
	}
	if (m_pKeyMgr->KeyPressing(VK_NUMPAD6))
	{
		if (!m_pKeyMgr->KeyPressing(VK_CONTROL))
			m_fAngle += D3DXToRadian(5.f);
	}

	D3DXMATRIX matScale, matRotate, matTrans;

	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, 1.f);
	D3DXMatrixRotationZ(&matRotate, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tMouse.x, m_tMouse.y,0.f);

	m_matWorld = matScale * matRotate * matTrans;
	if (m_pKeyMgr->KeyDown(VK_LBUTTON))
	{
		m_pObjMgr->InsertObject<CObstacle>(ObjectManager::OBSTACLE);
		dynamic_cast<CObstacle*>(m_pObjMgr->GetList(ObjectManager::OBSTACLE).back())->Respawn(m_iIndex,m_matWorld);
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

