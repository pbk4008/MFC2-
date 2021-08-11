#pragma once
#ifndef __SINGLE_TEXTURE_H__
#define __SINGLE_TEXTURE_H__

#include "Texture.h"
class SingleTexture : public Texture
{
private:
	explicit SingleTexture() {};
public:
	virtual ~SingleTexture();
	// Texture을(를) 통해 상속됨
	virtual TEXTINFO* GetTextInfo(const wstring& wstring = L"", const int& iCount = 0) override;
	virtual HRESULT InsertTexture(const wstring& wstrFilePath, const wstring& wstrStateKey = L"", const int& iCount = 0) override;
	virtual void ReleaseTexture() override;

public:
	static Texture* Create();

private:
	TEXTINFO textInfo;
};


#endif // !__SINGLE_TEXTURE_H__