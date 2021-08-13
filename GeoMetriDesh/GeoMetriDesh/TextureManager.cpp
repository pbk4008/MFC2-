#include "framework.h"
#include "TextureManager.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(TextureManager)

TextureManager::~TextureManager()
{
    Release();
}

HRESULT TextureManager::InsertTexture(FILE_ID _textID, const wstring& _filepath, const wstring& _objectKey, const wstring& _stateKey, const DWORD& _count)
{
    const auto& iter = textureMap.find(_objectKey);

    Texture* texture = nullptr;
    if (textureMap.end() == iter) {

        switch (_textID)
        {
        case TextureManager::SINGLE:
            texture = SingleTexture::Create();
            break;
        case TextureManager::MULTI:
            texture = MultiTexture::Create();
            break;
        }

        if (FAILED(texture->InsertTexture(_filepath, _stateKey, _count))) {
            return E_FAIL;
        }

        textureMap.emplace(_objectKey, texture);
        return S_OK;
    }
    else if (MULTI == _textID) {
        if (FAILED(iter->second->InsertTexture(_filepath, _stateKey, _count))) {
            return E_FAIL;
        }

        return S_OK;
    }

    return E_FAIL;
}

TEXTINFO* TextureManager::GetTextInfo(const wstring& _objectKey, const wstring& _stateKey, const DWORD& _count)
{
    const auto& iter_Find = textureMap.find(_objectKey);
    if (textureMap.end() == iter_Find)
        return nullptr;

    return iter_Find->second->GetTextInfo(_stateKey, _count);
}

void TextureManager::Release()
{
    for (auto& rPair : textureMap) {
        Safe_Delete(rPair.second);
    }

    textureMap.clear();
}
