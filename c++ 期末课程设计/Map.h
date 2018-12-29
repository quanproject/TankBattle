#pragma once
#include "Terrain.h"
#include"main_game.h"
//=============================地图类===============================//
class Map
{
public:
	Map();
	~Map();

	const bool GetTankAdmit(COORD xy) { return MT[xy.X/60][xy.Y/60].TankT; }       //返回坦克通行许可  坐标比例转换
	const bool GetShellAdmit(COORD xy) { return MT[xy.X/60][xy.Y/60].ShellT; }     //返回炮弹通行许可

	void ChangeMap(COORD xy);              //修改地图上的地形（减少HP)
	void CloseMap();                       //释放内存，结束游戏或准备下张地图

	void ReadyforAllMap();        //加载所有地图相同工作

	void ReadyforMap_one();     //加载第一关的准备工作
	void PrintMap_one();        //打印第一关

	void ReadyforMap_two();
	void PrintMap_two();
private:
	MapTerrain MT[20][14];    //全地图的炮弹/坦克通过标记(以60x60像素为单位 
	SteeWall *steewall;      //地形记录指针
	River *river;
	Brush *brush;
	int num_stee;            //各个地形的数量
	int num_river;
	int num_brush;

	//SteeWall testwall;       //测试墙

	short _x;    //用来画坐标
	short _y;
};

