#pragma once
#ifndef __MULTI_TEXTURE_H__
#define __MULTI_TEXTURE_H__

#include "Texture.h"
class MultiTexture : public Texture
{
private:
	explicit MultiTexture() {};
public:
	virtual ~MultiTexture();

	// Texture을(를) 통해 상속됨
	virtual TEXTINFO* GetTextInfo(const wstring& _wstring = L"", const int& _count = 0) override;
	virtual HRESULT InsertTexture(const wstring& _wstrFilePath, const wstring& _wstrStateKey = L"", const int& _count = 0) override;
	virtual void ReleaseTexture() override;

public:
	static Texture* Create();
private:
	map<wstring, vector<TEXTINFO*>> multiMap;
};




#endif // !__MULTI_TEXTURE_H__