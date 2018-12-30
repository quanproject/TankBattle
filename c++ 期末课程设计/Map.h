#pragma once
#include "Terrain.h"
#include"main_game.h"
#include"Tank.h"
//=============================地图类===============================//
class Map
{
public:
	Map();
	~Map();

	const bool GetTankAdmit(COORD xy) { return MT[xy.X/60][xy.Y/60].TankT; }       //返回坦克通行许可  坐标比例转换
	const bool GetShellAdmit(COORD xy) { return MT[xy.X/60][xy.Y/60].ShellT; }     //返回炮弹通行许可

	const int GetNumNormalTank(){return num_normaltank;}               //获取普通坦克数量
	const int GetNumBossTank() { return num_bosstank; }             //获取精英坦克数量
	void KillNormalTank() { --num_normaltank; }                     //减少坦克数量
	void KillBossTank() { --num_bosstank; }

	bool JudgmentBorder(COORD xy);         //判断物件是否超界
	void ChangeMap(COORD xy);              //修改地图上的地形（减少HP)
	const void PrintMap_1();               //打印地图(在坦克上面的
	const void PrintMap_2();               //打印地图（在坦克下面的
	void CloseMap();                       //释放内存，结束游戏或准备下张地图
	COORD CreatObjectXY(int h);                 //随机在地图上部范围内生成坐标，用来给野生坦克和野生buff提供出生点


	void ReadyforMap_one();     //加载第一关的准备工作
	void ReadyforMap_two();     //加载第二关准备工作
private:
	COORD Switchxy(COORD xy) { return { (xy.X / 60) ,(xy.Y / 60)  }; }   //转换坐标（将任意坐标 转换为 每60像素为一格的 左上角坐标
	MapTerrain MT[20][14];    //全地图的炮弹/坦克通过标记(以60x60像素为单位 

	SteeWall *steewall;      //地形记录指针
	River *river;
	Brush *brush;
	SodWall *sodwall;
	Home home;        //家就一个（或许x

	int num_stee;            //各个地形的数量
	int num_river;
	int num_brush;
	int num_sodwall;

	int num_normaltank;   //普通坦克数量
	int num_bosstank;     //精英坦克数量

	short _x;    //用来画坐标
	short _y;
};

