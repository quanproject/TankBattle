#pragma once
#include"main_game.h"
#include"Map.h"

//=============================菜单类===============================//
class TankGameMenu
{
public:
	void printTankGameMenu();           //打印开始界面
	void Inaugurated();                 //刷屏动画
	void Commeting();                   //游戏说明
	void GameOver();                     //玩家死亡
	TankGameMenu();
	~TankGameMenu();
private:

};


