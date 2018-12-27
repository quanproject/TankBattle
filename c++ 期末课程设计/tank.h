#pragma once

#include"Object.h"

//=======================================坦克类====================================//
class Tank :public Object
{
public:
	Tank();
	~Tank();
	virtual void MoveTank(Dir NewDir)=0;           //坦克移动
	virtual void Fire()=0;                         //开火
	void ChangeSpeed(int newspeed);                   //修改坦克速度
	void ChangeHp(int flag);                          //修改坦克血量
	void ChangeFireInterval(int Newinterval);         //修改攻击间隔
	void Setxy(COORD xy);                             //修改坦克位置
	void ChangeDir(Dir NewDir);                       //修改坦克方向
	void ChangeReadyForFire(int Ready);               //修改能否开炮的状态
	const COORD Getxy();                                  //获取坦克位置
	const int GetSpeed();                                 //获取坦克速度
	const Dir GetDir();                                   //获取坦克方向
	const int GetFireInterval();                          //获取攻击间隔
	const bool GetReadyForFire();                         //获取坦克能否开炮的状态
	void Print();                                         //打印坦克
	void FireIntevalFigure();                                 //计算开炮冷却是否好了

private:
	int Speed;           //坦克的移动速度
	int Hp;              //坦克血量
	int FireInterval;    //攻击间隔
	bool ReadyForFire;   //表示是否可以射击  1为可以

};

//派生玩家坦克类
class PlayTank :public Tank
{
public:
	void MoveTank(Dir newdir);        //重写移动，由玩家操作
	void Fire();            //重写由玩家控制开火
};

//普通ai坦克类(速度，攻速，血量变化
class NormalAITank :public Tank
{
	void NormalAI();          //普通坦克行动ai
};

//精英ai坦克类
class BossAITank :public Tank
{
	void BossAI();           //boss坦克ai
};