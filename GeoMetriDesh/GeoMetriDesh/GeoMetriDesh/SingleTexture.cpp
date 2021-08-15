#include "framework.h"
#include "SingleTexture.h"

SingleTexture::~SingleTexture()
{
    ReleaseTexture();
}

TEXTINFO* SingleTexture::GetTextInfo(const wstring& wstring/* = L""*/, const int& iCount/* = 0*/)
{
    return &textInfo;
}

HRESULT SingleTexture::InsertTexture(const wstring& wstrFilePath, const wstring& wstrStateKey /*= L""*/, const int& iCount/* = 0*/)
{
    if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &textInfo.imageInfo))) {
        return E_FAIL;
    }
    if (FAILED(D3DXCreateTextureFromFileEx(GraphicDevice::GetInstance()->GetDevice(),
            wstrFilePath.c_str(),
            textInfo.imageInfo.Width,
            textInfo.imageInfo.Height,
            textInfo.imageInfo.MipLevels,
            0,
            textInfo.imageInfo.Format,
            D3DPOOL_MANAGED,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            0,
            nullptr,
            nullptr,
            &textInfo.texture ))) 
    {
        return E_FAIL;
    }


    return S_OK;
}

void SingleTexture::ReleaseTexture()
{
    if (textInfo.texture) {
        textInfo.texture->Release();
    }
}

Texture* SingleTexture::Create()
{
    Texture* instance = new SingleTexture;
    return instance;
}
