#pragma once
#include"main_game.h"

//坦克类
class Tank
{
public:
	Tank();
	~Tank();
	void MoveTank();                   //坦克移动
	void ChangSpeed(int newspeed);     //修改坦克速度
	void ChangHp(int flag);
	void Fire();                //开火
	void Setxy(COORD xy);              //设置坦克初始位置
	void ChangeFireInterval(int Newinterval);         //修改攻击间隔
	void PrintTank();
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