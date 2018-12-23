#pragma once
#include"main_game.h"
//=============================地形类===============================//
class Terrain
{
public:
	Terrain();
	~Terrain();
	const void PrintTerrain();       //打印地形
private:
	bool TankThrough;             //Tank能否穿越
	bool ShellThrough;            //炮弹能否穿越
};
