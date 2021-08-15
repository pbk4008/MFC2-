#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct OBJINFO {
	D3DXVECTOR3 pos; // ��ġ
	D3DXVECTOR3 size; // ũ��
	D3DXVECTOR3 dir; // ����

	D3DXMATRIX mat; // ???? �̰� ����� ����
}INFO;


typedef struct TEXTINFO {
	LPDIRECT3DTEXTURE9 texture; // HBITMAP //��, �̹��� ������ ������ �İ�ü. 
	D3DXIMAGE_INFO		imageInfo;
}TEXTINFO;

#endif // !__STRUCT_H__
