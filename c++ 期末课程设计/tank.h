#pragma once

#include"Object.h"
#include"Shell.h"

//=======================================坦克类====================================//
class Tank :public Object
{
public:
	Tank();
	~Tank();
	virtual void MoveTank(Dir NewDir)=0;           //坦克移动
	virtual void Fire()=0;                         //开火

	void ChangeSpeed(int newspeed) { Speed = newspeed; }                                //修改坦克速度
	void ChangeFireInterval(int Newinterval) { FireInterval = Newinterval; }            //修改攻击间隔
	void Setxy(COORD xy) { XY = xy; }                                                   //修改坦克位置
	void ChangeDir(Dir NewDir) { Direction = NewDir; }                                  //修改坦克方向
	void ChangeReadyForFire(int ReadyOrNot) { ReadyForFire = ReadyOrNot; }              //修改能否开炮的状态
	const COORD Getxy() {return XY; }                                        //获取坦克位置
	const int GetSpeed() { return Speed; }                                   //获取坦克速度
	const Dir GetDir() { return Direction; }                                 //获取坦克方向
//	const int GetFireInterval() {return  FireInterval;}                      //获取攻击间隔
	bool GetReadyForFire() { return ReadyForFire; }                    //获取坦克能否开炮的状态
	const int GetHP() { return Hp; }                                         //获取坦克血量

	void ChangeHp(int flag);                          //修改坦克血量
	//void Print();                                     //打印坦克
	void FireIntevalFigure();                         //计算开炮冷却是否好了

protected:
	int Speed;           //坦克的移动速度
	int Hp;              //坦克血量
	int FireInterval;    //攻击间隔
	bool ReadyForFire;   //表示是否可以射击  1为可以
	int nowInterval;     //当前的攻击冷却进度

};

//派生玩家坦克类
class PlayTank :public Tank
{
public:
	PlayTank();
	void Print();
	void MoveTank(Dir newdir);  //移动由玩家操作
	void Fire();                //由玩家控制开火
};

//普通ai坦克类(速度，攻速，血量变化
class NormalAITank :public Tank
{
public:
	NormalAITank();
	Dir NormalMoveAI(int h);          //普通坦克移动ai
	void Print();
	void MoveTank(Dir NewDir);
	void Fire() {};

};

//精英ai坦克类
class BossAITank :public Tank
{
public:
	BossAITank();
	void Print();
	void BossAI();           //boss坦克ai
	void MoveTank(Dir NewDir) {};
	void Fire() {};
};