#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class Texture
{
public:
	inline explicit Texture() {};
	inline virtual ~Texture() {};

public:
	virtual TEXTINFO* GetTextInfo(const wstring& wstring = L"", const int& iCount = 0) PURE;
	virtual HRESULT InsertTexture(const wstring& wstrFilePath, const wstring& wstrStateKey = L"",	const int& iCount = 0) PURE;
	virtual void ReleaseTexture()PURE;
};


#endif // !__TEXTURE_H__