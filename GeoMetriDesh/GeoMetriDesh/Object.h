#pragma once
#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object
{
public:
	inline explicit Object() : deadCheck(false), checkClickEvent(false)
	{
		ZeroMemory(&info, sizeof(info));
		ZeroMemory(&rc, sizeof(rc));
		ZeroMemory(&pTextInfo, sizeof(pTextInfo));
		ZeroMemory(&centerVec, sizeof(centerVec));
		ZeroMemory(&rgb, sizeof(rgb));

		memset(lineList, 0, sizeof(lineList));
	};
	inline ~Object() {};

	inline virtual HRESULT ReadObject() PURE;
	inline virtual int UpdateObject() PURE;
	inline virtual void LateUpdateObject() PURE;
	inline virtual void RenderObject() PURE;
	inline virtual void ReleaseObject() PURE;

	inline D3DXVECTOR3& GetPos() { return  info.pos; };
	inline D3DXVECTOR3& GetDir() { return  info.dir; };
	inline D3DXVECTOR3& GetSize() { return  info.size; };
	inline D3DXMATRIX& GetMat() { return  info.mat; };

	inline bool GetDeadCheck() { return deadCheck; };
	inline bool GetCheckClickEvent() { return checkClickEvent;	}

	inline void SetDeadCheck(bool _b) { deadCheck = _b; };

	inline void SetPos(D3DXVECTOR3 _vecPos) { info.pos = _vecPos; };
	inline void SetDir(D3DXVECTOR3 _vecDir) { info.dir = _vecDir; };
	inline void SetSize(D3DXVECTOR3 _vecSize) { info.size = _vecSize; };
	inline void SetMat(D3DXMATRIX _vecMat) { info.mat = _vecMat; };

	inline RECT& GetRect() { return rc; };

	void SetObjectInfo();
	void UpdateObjectInfo();
	void DrawImage();

protected:
	INFO info;
	RECT rc;
	ARGB rgb;


	// �ҷ��� �̹��� ������ ����
	TEXTINFO* pTextInfo;

	// �̹��� ����
	// �浹 �׸� �뵵
	D3DXVECTOR2 lineList[5];

	// �̹��� ����
	D3DXVECTOR3 centerVec;

	// Ǯ�� check
	bool deadCheck;

	// ���콺 Ŭ�� �̺�Ʈ ��ȣ�ۿ� �������
	bool checkClickEvent;
};


#endif // !__OBJECT_H__