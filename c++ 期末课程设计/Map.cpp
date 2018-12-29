#include "Map.h"
using namespace std;

list<SodWall*> MapSodWall;            //储存地图上的可破坏墙
list<SodWall*>::iterator MSW;         //土墙

Map::Map()
{
}


Map::~Map()
{
}

void Map::ReadyforAllMap()
{
	num_stee = 20;
	steewall = new SteeWall [20];
	_x = 0;
	_y = 13;
	//地图下方的一排铁墙
	for (int i = 0; i < num_stee; i++)
	{
		steewall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y]=steewall[i].GetMapTerrain();           //设置地形属性
		_x++;
	}
	///////////////测试墙///////////////////////
	//testwall.SetXY({ 3,4 });
	//MT[3][4] = testwall.GetMapTerrain();
	////////////////////////////////////////
}


void Map::CloseMap()
{

}

void Map::ReadyforMap_one()
{

}

void Map::PrintMap_one()
{
	for (int i = 0; i < num_stee; i++)
	{
		steewall[i].Print();
	}
	////////////////测试墙//////////////////
	//testwall.Print();
	//////////////////////////////////////
}
