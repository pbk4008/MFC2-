#include "framework.h"
#include "Edit.h"
#include "TextureManager.h"
#include "KeyManager.h"

CEdit::CEdit() : m_pSprite(nullptr),m_pTextureMgr(nullptr), m_pKeyMgr(nullptr), m_iIndex(0)
{
	ZeroMemory(&m_tMouse, sizeof(POINT));
}

CEdit::~CEdit()
{
}

HRESULT CEdit::Initialize()
{
	m_pSprite = GraphicDevice::GetInstance()->GetSprite();
	m_pTextureMgr = TextureManager::GetInstance();
	m_pKeyMgr = KeyManager::GetInstance();

	m_pTextureMgr->InsertTexture(TextureManager::MULTI, L"../Texture/Obstacle/Obstacle00%d.png", L"Tile", L"Obstacle", 6);
	return S_OK;
}

int CEdit::Update()
{
	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);
	if (m_pKeyMgr->KeyDown(VK_UP))
		m_iIndex++;
	
	if (m_pKeyMgr->KeyDown(VK_DOWN))
		m_iIndex--;
	
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
	const TEXTINFO* pTexture = m_pTextureMgr->GetTextInfo(L"Tile", L"Obstacle", m_iIndex);

	float fCenterX = float(pTexture->imageInfo.Width >> 1);
	float fCenterY = float(pTexture->imageInfo.Height >> 1);

	D3DXVECTOR3 vecCenter{ fCenterX, fCenterY, 0.f };
	D3DXVECTOR3 vecMouse{ float(m_tMouse.x), float(m_tMouse.y), 0.f };
	m_pSprite->Draw(pTexture->texture, nullptr, &vecCenter, &vecMouse, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CEdit::Release()
{
}

Scene* CEdit::Create()
{
	Scene* pInstance = new CEdit();
	if (FAILED(pInstance->Initialize()))
		SAFE_DELETE(pInstance);
	return pInstance;
}
