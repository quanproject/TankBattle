#pragma once

#include"main_game.h"
//=========================物件类 （所有坦克、炮弹、buff的父类）====================//
class Object
{
public:
	virtual void Print()=0;
protected:
	Dir Direction;  //方向
	COORD XY;       //左上角坐标
	int RectSphere; //像素大小
};