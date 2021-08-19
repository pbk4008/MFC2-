#include "framework.h"
#include "Edit.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "ScrollMgr.h"
#include "ObjectManager.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "Line.h"
#include "Land.h"
#include "Obstacle.h"
#include "Player.h"

CEdit::CEdit() : m_pLand(nullptr), m_pObjMgr(nullptr), m_pScrollMgr(nullptr),m_pSprite(nullptr),m_pTextureMgr(nullptr), m_pKeyMgr(nullptr), m_pLineMgr(nullptr),
m_bTile(false), m_bFirst(false), m_bRemove(false),
m_iIndex(0)
{
	ZeroMemory(&m_tMouse, sizeof(POINT));
	ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
	ZeroMemory(&m_matWorld, sizeof(D3DXMATRIX));
	ZeroMemory(&m_MouseMatrix, sizeof(D3DXMATRIX));
	ZeroMemory(&m_tMouseRect, sizeof(RECT));

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
	m_pObjMgr->Intialize();
	m_pLineMgr->LoadLine();

	m_pTextureMgr->InsertTexture(TextureManager::MULTI, L"../Texture/Obstacle/Obstacle00%d.png", L"Tile", L"Obstacle", 19);
	
	m_pLand = new CLand();
	m_pLand->ReadObject();

	m_fSize = 1.f;
	m_pScrollMgr->reSetSpeed();
	m_pObjMgr->InsertObject<Player>(ObjectManager::PLAYER);
	return S_OK;
}

int CEdit::Update()
{
	m_pScrollMgr->XUpdate();

	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);
	if (m_pKeyMgr->KeyDown('1'))
	{
		m_bTile = false;
		m_bRemove = false;
	}
	if (m_pKeyMgr->KeyDown('2'))
	{
		m_bRemove = false;
		m_bTile = true;
		m_iIndex = 0;
	}
	if (m_pKeyMgr->KeyDown('3'))
	{
		m_bRemove = false;
		m_bTile = true;
		m_iIndex = 6;
	}
	if (m_pKeyMgr->KeyDown('4'))
	{
		m_bRemove = true;
		m_bTile = false;
	}
	if (m_pKeyMgr->KeyPressing(VK_RIGHT))
		m_pScrollMgr->setScrollX(5.f);
	if(m_pKeyMgr->KeyPressing(VK_LEFT))
		m_pScrollMgr->setScrollX(-5.f);
	if (m_pKeyMgr->KeyPressing('Q'))
		m_pScrollMgr->setScrollY(5.f);
	if (m_pKeyMgr->KeyPressing('W'))
		m_pScrollMgr->setScrollY(-5.f);
	if (m_pKeyMgr->KeyDown('S'))
		m_pLineMgr->SaveLine();
	if (m_pKeyMgr->KeyDown('A'))
		m_pLineMgr->LoadLine();

	if (m_pKeyMgr->KeyDown('K'))
		m_pObjMgr->SaveObject();
	if (m_pKeyMgr->KeyDown('J'))
		m_pObjMgr->LoadObject();

	/*if(m_pKeyMgr->KeyDown(VK_SPACE))
		m_pScrollMgr->setSpeed(1.f);*/


	if (m_bTile)
		CreateTile();
	else
		CreateLine();

	/*m_pLand->UpdateObject();*/

	if (m_bRemove)
		Remove();

	m_pObjMgr->Update();
	return 0;
}

void CEdit::LateUpdate()
{
	if (m_iIndex < 0)
		m_iIndex = 0;
	if (m_iIndex > 18)
		m_iIndex = 18;
}

void CEdit::Render()
{
	if (m_bTile)
	{
		const TEXTINFO* pTexture = m_pTextureMgr->GetTextInfo(L"Tile", L"Obstacle", m_iIndex);

		float fCenterX = float(pTexture->imageInfo.Width >> 1);
		float fCenterY = float(pTexture->imageInfo.Height >> 1);
		float fScrollX = m_pScrollMgr->getScrollX();
		float fScrollY = m_pScrollMgr->getScrollY();

		D3DXVECTOR3 vecCenter{ fCenterX, fCenterY, 0.f };
	
		m_pSprite->SetTransform(&m_MouseMatrix);
		m_pSprite->Draw(pTexture->texture, nullptr, &vecCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	if (m_bRemove)
	{
		D3DXVECTOR2 arg[5] = {};

		arg[0] = { float(m_tMouseRect.left), float(m_tMouseRect.top) };
		arg[1] = { float(m_tMouseRect.right), float(m_tMouseRect.top) };
		arg[2] = { float(m_tMouseRect.right), float(m_tMouseRect.bottom) };
		arg[3] = { float(m_tMouseRect.left), float(m_tMouseRect.bottom) };
		arg[4] = { float(m_tMouseRect.left), float(m_tMouseRect.top) };
	

		m_pSprite->End();
		GraphicDevice::GetInstance()->GetLine()->SetWidth(2.f);
		GraphicDevice::GetInstance()->GetLine()->Draw(arg, 5, D3DCOLOR_ARGB(255, 255, 0, 0));
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	m_pLineMgr->Render();
	m_pObjMgr->Render();
	m_pLand->RenderObject();
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

	float fY = 0;
	float fX = 0;
	D3DXMATRIX matScale, matRotate, matTrans, matMousMove;

	float fScrollX = m_pScrollMgr->getScrollX();
	float fScrollY = m_pScrollMgr->getScrollY();

	D3DXMatrixScaling(&matScale, m_fSize, m_fSize, 1.f);
	D3DXMatrixRotationZ(&matRotate, m_fAngle);
	
	if (!m_pObjMgr->GetList(ObjectManager::OBSTACLE).empty())
	{
		fX = dynamic_cast<CObstacle*>(m_pObjMgr->GetList(ObjectManager::OBSTACLE).back())->getObstacleInfo().tMatrix._41-fScrollX;
		fY = dynamic_cast<CObstacle*>(m_pObjMgr->GetList(ObjectManager::OBSTACLE).back())->getObstacleInfo().tMatrix._42-fScrollY;
	}
	if (m_pKeyMgr->KeyPressing(VK_SHIFT))
	{
		D3DXMatrixTranslation(&matTrans, m_tMouse.x + fScrollX, fY+fScrollY, 0.f);
		D3DXMatrixTranslation(&matMousMove, m_tMouse.x, fY, 0.f);
	}
	else if (m_pKeyMgr->KeyPressing(VK_CONTROL))
	{
		D3DXMatrixTranslation(&matTrans, fX+fScrollX, m_tMouse.y + fScrollY, 0.f);
		D3DXMatrixTranslation(&matMousMove, fX, m_tMouse.y, 0.f);
	}
	else
	{
		D3DXMatrixTranslation(&matTrans, m_tMouse.x + fScrollX, m_tMouse.y + fScrollY, 0.f);
		D3DXMatrixTranslation(&matMousMove, m_tMouse.x, m_tMouse.y, 0.f);
	}
	m_matWorld = matScale * matRotate * matTrans;
	m_MouseMatrix = matScale * matRotate * matMousMove;
	
	if (m_pKeyMgr->KeyDown(VK_LBUTTON))
	{
		m_pObjMgr->InsertObject<CObstacle>(ObjectManager::OBSTACLE);
		dynamic_cast<CObstacle*>(m_pObjMgr->GetList(ObjectManager::OBSTACLE).back())->Respawn(m_iIndex, m_matWorld);
	}
	if (m_pKeyMgr->KeyDown(VK_RBUTTON))
	{
		Safe_Delete(m_pObjMgr->GetList(ObjectManager::OBSTACLE).back());
		m_pObjMgr->GetList(ObjectManager::OBSTACLE).pop_back();
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
	if (m_pKeyMgr->KeyDown('Z'))
	{
		m_pLineMgr->DeleteLine();
	}
}

void CEdit::Remove()
{
	float OffSet = 10.f;
	float fScrollX = m_pScrollMgr->getScrollX();
	float fScrollY = m_pScrollMgr->getScrollY();
	m_tMouseRect = { LONG(m_tMouse.x - OffSet), LONG(m_tMouse.y - OffSet), LONG(m_tMouse.x + OffSet), LONG(m_tMouse.y + OffSet) };
	RECT RemoveRect = { LONG(m_tMouse.x - OffSet+fScrollX), LONG(m_tMouse.y - OffSet+ fScrollY), LONG(m_tMouse.x + OffSet + fScrollX), LONG(m_tMouse.y + OffSet+fScrollY) };
	RECT rc = {};
	size_t iSize = m_pObjMgr->GetList(ObjectManager::OBSTACLE).size();

	if (!m_pObjMgr->GetList(ObjectManager::OBSTACLE).empty())
	{
		auto iter = m_pObjMgr->GetList(ObjectManager::OBSTACLE).begin();
		for (;iter != m_pObjMgr->GetList(ObjectManager::OBSTACLE).end();)
		{
			if (IntersectRect(&rc, &RemoveRect, &(*iter)->GetRect())) {
				// 플레이어죽음
				Safe_Delete((*iter));
				iter=m_pObjMgr->GetList(ObjectManager::OBSTACLE).erase(iter);
			}
			else
				iter++;
		}
	}
	
}

