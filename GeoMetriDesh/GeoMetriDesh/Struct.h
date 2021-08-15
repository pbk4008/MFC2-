#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct OBJINFO {
	D3DXVECTOR3 pos; // 위치
	D3DXVECTOR3 size; // 크기
	D3DXVECTOR3 dir; // 방향

	D3DXMATRIX mat; // ???? 이건 어따씀 ㅋㅋ
}INFO;


typedef struct TEXTINFO {
	LPDIRECT3DTEXTURE9 texture; // HBITMAP //즉, 이미지 한장을 제어할 컴객체. 
	D3DXIMAGE_INFO		imageInfo;
}TEXTINFO;

#endif // !__STRUCT_H__
