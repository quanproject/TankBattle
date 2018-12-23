#pragma once

#include"main_game.h"
//=============================炮弹类===============================//
class Shell
{
public:
	Shell(int dir, COORD xy);
	~Shell();
	void Print();                        //打印炮弹
	void Fly();                          //炮弹飞行判断函数
	const COORD GetShellxy();            //获取炮弹坐标（用于判断是否命中

private:
	int Direction;          //炮弹行进的方向
	COORD XY;               //炮弹的当前坐标
	int Flag;
};


////////////////////////////类的实现//////////////////////////////
