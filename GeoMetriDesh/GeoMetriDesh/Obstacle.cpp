#include "framework.h"
#include "Obstacle.h"
#include "TextureManager.h"
#include "ScrollMgr.h"

CObstacle::CObstacle() : m_pScrollMgr(nullptr)
{
	m_pSprite = GraphicDevice::GetInstance()->GetSprite();
	ZeroMemory(&m_tObstacleInfo, sizeof(OBSTACLEINFO));
}

CObstacle::~CObstacle()
{
	ReleaseObject();
}

HRESULT CObstacle::ReadObject()
{
	m_pScrollMgr = CScrollMgr::GetInstance();
	return S_OK;
}

int CObstacle::UpdateObject()
{
	/*float fScollX = m_pScrollMgr->getUpdateScrollX();
	float fScollY = m_pScrollMgr->getUpdateScrollY();
	D3DXMATRIX argTrans;
	D3DXMatrixTranslation(&argTrans, -m_pScrollMgr->getSpeed(), 0.f, 0.f);
	m_tObstacleInfo.tMatrix *= argTrans;
	info.size.x = OBSTACLECX*m_tObstacleInfo.tMatrix._11;
	info.size.y = OBSTACLECY*m_tObstacleInfo.tMatrix._22;
	info.size.z = 0.f;

	info.pos.x = m_tObstacleInfo.tMatrix._41;
	info.pos.y = m_tObstacleInfo.tMatrix._42;
	info.pos.z = 0.f;*/

	UpdateObjectInfo();
	return 0;
}

void CObstacle::LateUpdateObject()
{
}

void CObstacle::RenderObject()
{
	float fScrollX = m_pScrollMgr->getUpdateScrollX();
	float fScrollY = m_pScrollMgr->getScrollY();

	D3DXMATRIX matShow = {};
	matShow = m_tObstacleInfo.tMatrix;

	matShow._41 = m_tObstacleInfo.tMatrix._41 - fScrollX;
	matShow._42 = m_tObstacleInfo.tMatrix._42 + fScrollY;
	m_pSprite->SetTransform(&matShow);
	m_pSprite->Draw(pTextInfo->texture, nullptr, &centerVec, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	/*m_pSprite->SetTransform(&(m_tObstacleInfo.tMatrix));
	
	DrawImage();*/
}
	

void CObstacle::ReleaseObject()
{
}

void CObstacle::Respawn(const OBSTACLEINFO& _Info)
{
	deadCheck = false;
	setIndex(_Info.iIndex);
	setMatrix(_Info.tMatrix);
	pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Tile", L"Obstacle", m_tObstacleInfo.iIndex);
	rgb = { 255,255,255,255 };
	SetObjectInfo();
}

void CObstacle::Respawn(const int& _iIndex, const D3DMATRIX& _matMatrix)
{
	setIndex(_iIndex);
	setMatrix(_matMatrix);
	pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Tile", L"Obstacle", m_tObstacleInfo.iIndex);
	rgb = { 255,255,255,255 };
	SetObjectInfo();
}
