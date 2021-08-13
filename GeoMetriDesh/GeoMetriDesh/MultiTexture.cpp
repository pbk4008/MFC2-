#include "framework.h"
#include "MultiTexture.h"

MultiTexture::~MultiTexture()
{
    ReleaseTexture();
}

TEXTINFO* MultiTexture::GetTextInfo(const wstring& _wstring/* = L""*/, const int& _count/* = 0*/)
{
    const auto& iter = multiMap.find(_wstring);
    if (multiMap.end() == iter) {
        return nullptr;
    }
    if (iter->second.size() < _count) {
        return nullptr;
    }

    return iter->second[_count];
}

HRESULT MultiTexture::InsertTexture(const wstring& _wstrFilePath, const wstring& _wstrStateKey /*= L""*/, const int& _count/* = 0*/)
{
    const auto& iter = multiMap.find(_wstrStateKey);
	if (multiMap.end() == iter) {
		TCHAR szBuf[MAX_PATH] = L"";
		TEXTINFO* pTexInfo = nullptr;
		for (int i = 0; i < _count; ++i)
		{
			pTexInfo = new TEXTINFO;
			swprintf_s(szBuf, _wstrFilePath.c_str(), i);
			//L"../Texture/Stage/Player/Attack/AKIHA_AKI01_000.png"
			if (FAILED(D3DXGetImageInfoFromFile(szBuf, &pTexInfo->imageInfo)))
				return E_FAIL;

			if (FAILED(D3DXCreateTextureFromFileEx(GraphicDevice::GetInstance()->GetDevice(),
				szBuf,
				pTexInfo->imageInfo.Width,
				pTexInfo->imageInfo.Height,
				// �̹��� ũ�⸦ ������ �غ��ؼ� ��� �� Ȯ�� ����� �´� �̹��� ũ�⸦ ���� �۾��ϱ� ���� ������. �������� �ְ� ���� ���� ����. 
				pTexInfo->imageInfo.MipLevels,
				0,
				pTexInfo->imageInfo.Format,
				// �޸� ������ ��� ����� ���̳� �ý��� �޸� ���̳� �׷��� īƮ�� �޸� ������ ����� ���̳�. 
				//D3DPOOL_MANAGED, - �̰� �׷��� īƮ �޸� ������ ����ϵ� �����ϸ� �����ٰ��� �����ϱ� ������ ������ + �ӵ��� �� ì��. 
				D3DPOOL_MANAGED,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				0,
				nullptr,
				nullptr,
				&pTexInfo->texture)))
				return E_FAIL;

			multiMap[_wstrStateKey].emplace_back(pTexInfo);
			//vector<TEXINFO*>.emplace_back(pTexInfo);
		}
		return S_OK;
	}

    return E_FAIL;
}

void MultiTexture::ReleaseTexture()
{
	for (auto& rPair : multiMap)
	{
		for (auto& pTexInfo : rPair.second)
			SAFE_DELETE(pTexInfo);
		rPair.second.clear();
		rPair.second.shrink_to_fit(); // capacity ����� �ʱ�ȭ
	}
}

Texture* MultiTexture::Create()
{
	Texture* instance = new MultiTexture;
    return instance;
}
