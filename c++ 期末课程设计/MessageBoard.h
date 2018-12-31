#pragma once
#include"main_game.h"
#include"Tank.h"
//=============================信息版类===============================//
class MessageBoard
{
public:
	MessageBoard();
	~MessageBoard();
	const void Print();                            //打印信息板子
	void ChangeTankMessage(PlayTank tank);         //修改信息板信息
	void ChangeCard(int car) { card = car; }       //修改关卡
private:
	int Speed;           //坦克的移动速度
	int Hp;              //坦克血量
	int FireInterval;    //攻击间隔
	int card;            //第几关
	COORD XY;            //信息板的位置
};

