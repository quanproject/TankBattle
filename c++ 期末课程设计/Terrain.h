#pragma once
#include"main_game.h"
//=============================地形类（各个地形的基类）===============================//
class Terrain
{
public:
	Terrain();
	~Terrain();
	void SetXY(COORD xy) { XY.X = xy.X * 60; XY.Y = xy.Y * 60; }   //设定坐标
	const COORD GetXY() { return { XY.X / 60,XY.Y/60 }; }          //获取坐标
	virtual void Print() = 0;       //打印地形
	const int GetHP() { return HP; }       //用来判断地形是否还存在
	const MapTerrain GetMapTerrain(){return mapterrain;}    //获取地图穿越信息
	void Destory() { HP--; }              //减少墙的HP
protected:
	MapTerrain mapterrain;      //tank/炮弹能否穿越的信息
	COORD XY;
	int HP;
};

//const int SODWALL = 5;     //土墙 易破坏的墙
//const int STEEWALL = 6;    //铁墙 不易破坏的墙
//const int BRUSH = 7;       //灌木 坦克可以穿越 炮弹无法穿过
//const int RIVER = 8;       //河流 坦克不能穿越 炮弹可以穿越



//铁墙类
class SteeWall :public Terrain
{
public:
	SteeWall();
	void Print();
};

//土墙类
class SodWall :public Terrain
{
public:
	SodWall();
	void Print();
};

//灌木类
class Brush :public Terrain
{
public:
	Brush();
	void Print();
};

//河流类
class River :public Terrain
{
public:
	River();
	void Print();
private:
	int Dynamic;      //河流动态效果实现
};

//家园类
class Home :public Terrain
{
public:
	Home();
	void Print();
};