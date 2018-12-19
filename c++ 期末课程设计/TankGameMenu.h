#pragma once
//坦克大战菜单类
#include"main_game.h"
#include"Tank.h"
class TankGameMenu
{
public:
	void printTankGameMenu();           //打印开始界面
	void Inaugurated();                 //刷屏动画
	void GameStart(int card);           //游戏开始(card决定哪个关卡
	void Commeting();                   //游戏说明
	TankGameMenu();
	~TankGameMenu();
private:

};


