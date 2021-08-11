#include "framework.h"
#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class Player;
class GraphicDevice;
class MainGame
{
private:
	explicit MainGame();
public:
	virtual ~MainGame();


private:
	HRESULT ReadyMainGame();

public:
	void UpdateMainGame();
	void LateUpdateMainGame();
	void RenderMainGame();
	void ReleaseMainGame();

	static MainGame* Create();

private:
	GraphicDevice* graphicDevice;

	Player* player;
};





#endif // !__MAINGAME_H__