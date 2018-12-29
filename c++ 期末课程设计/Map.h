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

	bool JudgmentBorder(COORD xy);         //判断物件是否超界
	void ChangeMap(COORD xy);              //修改地图上的地形（减少HP)
	const void PrintMap_1();                  //打印地图(在坦克上面的
	const void PrintMap_2();                  //打印地图（在坦克下面的
	void CloseMap();                       //释放内存，结束游戏或准备下张地图


	void ReadyforMap_one();     //加载第一关的准备工作
	void ReadyforMap_two();
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

	SodWall testwall;       //测试墙

	short _x;    //用来画坐标
	short _y;
};

