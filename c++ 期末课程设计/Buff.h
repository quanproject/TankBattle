#pragma once
#include"main_game.h"
#include"Object.h"
//=============================增益类===============================//
class Buff:public Object
{
public:
	Buff();
	~Buff();
	virtual void BuffEffect()=0;           //buff效果
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
	void Print();
};