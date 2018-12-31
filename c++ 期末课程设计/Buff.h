#pragma once
#include"main_game.h"
#include"Object.h"
#include"Tank.h"
//=============================增益类===============================//
class Buff:public Object
{
public:
	Buff();
	~Buff();
	virtual void BuffEffect(PlayTank &tank)=0;           //buff效果
	void Setxy(COORD xy) { XY = xy; }      //设定坐标
	COORD Getxy() { return XY; };          //返回坐标
protected:
	int Dynamic;      //动态效果实现
};

class MoveSpeedBuff:public Buff
{
public:
	void BuffEffect(PlayTank &tank);
	void Print();
};

class FireIntervalBuff :public Buff
{
public:
	void BuffEffect(PlayTank &tank);
	void Print();
};

class HPBuff :public Buff
{
public:
	void BuffEffect(PlayTank &tank);
	void Print();
};
