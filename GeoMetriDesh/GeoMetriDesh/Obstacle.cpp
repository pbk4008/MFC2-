#include "framework.h"
#include "Obstacle.h"
#include "TextureManager.h"

CObstacle::CObstacle()
{
	m_pSprite = GraphicDevice::GetInstance()->GetSprite();
	ZeroMemory(&m_tObstalceInfo, sizeof(OBSTACLEINFO));
}

CObstacle::~CObstacle()
{
	ReleaseObject();
}

HRESULT CObstacle::ReadObject()
{
	return S_OK;
}

int CObstacle::UpdateObject()
{
	return 0;
}

void CObstacle::LateUpdateObject()
{
}

void CObstacle::RenderObject()
{
	m_pSprite->SetTransform(&(m_tObstalceInfo.tMatrix));
	m_pSprite->Draw(pTextInfo->texture, nullptr, &centerVec, nullptr, D3DCOLOR_ARGB(rgb.A, rgb.R, rgb.G, rgb.B));
}

void CObstacle::ReleaseObject()
{
}

void CObstacle::Respawn(const int _iIndex, const D3DXMATRIX& _matrix)
{
	setIndex(_iIndex);
	setMatrix(_matrix);
	pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Tile", L"Obstacle", _iIndex);
	rgb = { 255,255,255,255 };
	SetObjectInfo();
}
