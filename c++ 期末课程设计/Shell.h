#pragma once

#include "Object.h"
//=============================炮弹类===============================//
class Shell :public Object
{
public:
	Shell(Dir facedir, COORD xy);
	~Shell();
	COORD GetXY();     //获取炮弹坐标
	Dir GetDir() { return Direction; }   //获取炮弹方向
	void Fly();
	void Print();
	void PrintShellBoom();
private:
	int Flag;
};

