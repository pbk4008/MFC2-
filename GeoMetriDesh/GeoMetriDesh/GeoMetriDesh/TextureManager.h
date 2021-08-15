#pragma once
#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

class Texture;
class TextureManager
{
	DECLARE_SINGLETON(TextureManager)
private:
	explicit TextureManager() {};
	virtual ~TextureManager();
public:
	enum FILE_ID {SINGLE, MULTI, TEX_END};
public:
	HRESULT InsertTexture(FILE_ID _textID,
		const wstring& _filepath,
		const wstring& _objectKey,
		const wstring& _stateKey = L"",
		const DWORD& _count = 0);

	TEXTINFO* GetTextInfo(const wstring& _objectKey,
		const wstring& _stateKey = L"",
		const DWORD& _count = 0);
	void Release();

private:
	map<wstring, Texture*> textureMap;
};


#endif // !__TEXTURE_MANAGER_H__