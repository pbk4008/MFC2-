#include "framework.h"
#include "Land.h"
#include "TextureManager.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CLand::CLand() : m_fLandDist(0.f), m_pSprite(nullptr), m_pScrollMgr(nullptr)
{
	ZeroMemory(&m_fLandStart, sizeof(D3DXVECTOR2));
	ZeroMemory(&m_fLandEnd, sizeof(D3DXVECTOR2));
}

CLand::~CLand()
{
}

HRESULT CLand::ReadObject()
{
	m_pScrollMgr = CScrollMgr::GetInstance();
	pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Tile",L"Obstacle",5);
	m_pSprite = GraphicDevice::GetInstance()->GetSprite();
	m_fLandDist = CLineMgr::GetInstance()->getLineDist(m_fLandStart, m_fLandEnd);
	SetObjectInfo();

	m_pScrollMgr->reSetSpeed();
	m_pScrollMgr->setSpeed(3.f);
	m_tRGBInfo = { 255,0,0,255 };

	return S_OK;
}

int CLand::UpdateObject()
{
	m_pScrollMgr->XUpdate();

	return 0;
}

void CLand::LateUpdateObject()
{
}

void CLand::RenderObject()
{
	float fOffsetY = 200.f;
	float fOffsetX = -10.f;
	float fSclloX = m_pScrollMgr->getUpdateScrollX();
	int iSize = m_fLandDist / LANDCX;
	for (int i = 0; i < iSize; i++)
	{
		D3DXVECTOR3 vecPos = { fOffsetX +(LANDCX*3.5f * i) + m_fLandStart.x + centerVec.x-fSclloX,m_fLandStart.y + centerVec.y+ fOffsetY,0.f };
		D3DXMATRIX matScale,matTrans;

		D3DXMatrixScaling(&matScale, 3.5f, 7.f, 1.f);
		D3DXMatrixTranslation(&matTrans, vecPos.x, vecPos.y, 0.f);
		info.mat = matScale*matTrans;
		m_pSprite->SetTransform(&info.mat);
		m_pSprite->Draw(pTextInfo->texture, nullptr, &centerVec, nullptr, D3DCOLOR_ARGB(m_tRGBInfo.A, m_tRGBInfo.R, m_tRGBInfo.G, m_tRGBInfo.B));
	}
}

void CLand::ReleaseObject()
{
}
