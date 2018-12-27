#pragma once

#include"main_game.h"
//=========================物件类 （所有坦克、炮弹、buff、地形的父类）====================//
class Object
{
public:
	virtual void Print()=0; //需要打印
	                        //有碰撞效果
protected:
	Dir Direction;  //方向
	COORD XY;       //左上角坐标
	int RectSphere; //像素大小
};