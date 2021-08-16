#include "framework.h"
#include "Land.h"
#include "TextureManager.h"

CLand::CLand() : m_fLandDist(0.f)
{
}

CLand::~CLand()
{
}

HRESULT CLand::ReadObject()
{
	pTextInfo = TextureManager::GetInstance()->GetTextInfo(L"Tile",L"Obstacle",5);
	return S_OK;
}

int CLand::UpdateObject()
{
	return 0;
}

void CLand::LateUpdateObject()
{
}

void CLand::RenderObject()
{

}

void CLand::ReleaseObject()
{
}
