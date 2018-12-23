#pragma once
#include"main_game.h"
//=============================增益类===============================//
class Buff
{
public:
	Buff();
	~Buff();
	void CreatBuff();                      //生成buff
	void GetBuff();                        //获得buff
	virtual void BuffEffect()=0;           //buff效果
	virtual const void PrintBuff() = 0;    //打印buf
};

class MoveSpeedBuff:public Buff
{
public:
	void BuffEffect();
};

class FireIntervalBuff :public Buff
{
public:
	void BuffEffect();
};

class HPBuff :public Buff
{
public:
	void BuffEffect();
};