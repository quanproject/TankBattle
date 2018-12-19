#pragma once
#include"main_game.h"

//坦克类
class Tank
{
public:
	Tank();
	~Tank();
	void MoveTank();                                  //坦克移动
	void ChangeSpeed(int newspeed);                   //修改坦克速度
	void ChangeHp(int flag);                          //修改坦克血量
	void ChangeFireInterval(int Newinterval);         //修改攻击间隔
	void Setxy(COORD xy);                             //修改坦克位置
	COORD Getxy();                                    //获取坦克位置
	int GetSpeed();                                   //获取坦克速度
	int GetDir();                                     //获取坦克方向
	void ChangeDir(int newdir);                       //修改坦克方向
	void Fire();                                      //开火
	void PrintTank();                                 //打印坦克
	//修改攻速 
private:
	int Speed;           //坦克的移动速度
	int Hp;              //坦克血量
	int Dir;             //坦克面向的方向
	int FireInterval;    //攻击间隔
	COORD XY;            //记录坦克坐标
};

//派生玩家坦克类
class PlayTank :public Tank
{
public:
	void MoveTank();        //重写移动，由玩家操作
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