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
				// 이미지 크기를 여러개 준비해서 축소 및 확대 연산시 맞는 이미지 크기를 얻어와 작업하기 위해 존재함. 있을수도 있고 없을 수도 있음. 
				pTexInfo->imageInfo.MipLevels,
				0,
				pTexInfo->imageInfo.Format,
				// 메모리 공간을 어디껄 사용할 것이냐 시스템 메모리 쪽이냐 그래픽 카트의 메모리 공간을 사용할 것이냐. 
				//D3DPOOL_MANAGED, - 이건 그래픽 카트 메모리 공간을 사용하되 부족하면 렘에다가도 보관하기 때문에 안정성 + 속도를 다 챙김. 
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
		rPair.second.shrink_to_fit(); // capacity 사이즈도 초기화
	}
}

Texture* MultiTexture::Create()
{
	Texture* instance = new MultiTexture;
    return instance;
}
