#include "Map.h"
using namespace std;



bool const cor_cmp(COORD pt1, COORD pt2);

Map::Map()
{
}


Map::~Map()
{
}


bool Map::JudgmentBorder(COORD xy)
{
	if (xy.X > 1200 || xy.X < 0 || xy.Y < 0)
		return 1;                                   //超界
	return 0;           //未超界
}

void Map::ChangeMap(COORD xy)
{
	int i;
	COORD _xy=Switchxy(xy);  //转换坐标
	MapTerrain allthrough;   //任意可穿越地形

	for (i = 0; i < num_sodwall; i++)
		if (cor_cmp(_xy, sodwall[i].GetXY()))   //寻找被破坏的墙
		{
			sodwall[i].Destory();
			break;
		}

	if (sodwall[i].GetHP() == 0)     //让被破坏的墙可以被穿越
		MT[_xy.X][_xy.Y]= allthrough;

}

void Map::CloseMap()
{
	delete[] sodwall;
	delete[] steewall;
	delete[] river;
	delete[] brush;
}

void Map::ReadyforMap_one()
{
	num_stee = 26;           //设置本关各个物件数量
	num_river = 12;
	num_brush = 8;
	num_sodwall = 120;
	num_normaltank = 10;
	num_bosstank = 2;

	steewall = new SteeWall[num_stee];
	river = new River[num_river];
	brush = new Brush[num_brush];
	sodwall = new SodWall[num_sodwall];

	int i;

	//地图下方的一排铁墙
	_x = 0;
	_y = 13;
	for (i = 0; i < 20; i++)
	{
		steewall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = steewall[i].GetMapTerrain();           //设置地形属性
		_x++;
	}

	//地图中间的铁墙
	_x = 7;
	_y = 7;
	for (i = 20; i < num_stee; i++)
	{
		steewall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = steewall[i].GetMapTerrain();           //设置地形属性
		_x++;
	}

	//设置所有河流
	_x = 1;
	_y = 5;
	for (i = 0; i < num_river; i++)
	{
		river[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = river[i].GetMapTerrain();           //设置地形属性
		_x++;
		if (i == 4)
			_x += 8;
		else if (i == 9)
		{
			_x = 9;
			_y++;
		}
	}

	//设置所有灌木
	_x = 8;
	_y = 3;
	for (i = 0; i < num_brush; i++)
	{
		brush[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = brush[i].GetMapTerrain();           //设置地形属性
		_x++;
		if (i == 3)
		{
			_x = 6;
			_y = 7;
		}
		else if (i == 4||i==6)
			_x = 13;
		else if (i == 5)
		{
			_x = 6;
			_y = 11;
		}
	}

	//设置所有的土墙
	_x = 0;
	_y = 0;
	for (i = 0; i <18; ++i)
	{
		sodwall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = sodwall[i].GetMapTerrain();           //设置地形属性
		++_x;
		if (i == 5)
		{
			++_x;
			++_y;
		}
		else if (i == 11)
		{
			++_x;
			--_y;
		}
	}
	_x = 1;
	_y = 2;
	for (i = 18; i < 50; ++i)
	{
		sodwall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = sodwall[i].GetMapTerrain();           //设置地形属性
		++_x;
		if (i == 19 || i == 23||i==27||i==31||i==35||i==39||i==43||i==47)
			++_x;
		else if (i == 21||i==29||i==37||i==45)
			_x += 8;
		else if (i == 25||i==41)
		{
			++_y;
			_x = 1;
		}
		else if (i == 33)
		{
			_y=8;
			_x = 1;
		}
	}
	_x = 1;
	_y = 4;
	for (i = 50; i < 80; i++)
	{
		sodwall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = sodwall[i].GetMapTerrain();           //设置地形属性
		++_x;
		if (i == 55)
			_x += 6;
		else if (i == 61)
		{
			_y = 7;
			_x = 0;
		}
		else if (i == 67)
			_x += 8;
		else if (i == 73)
		{
			_x = 7;
			_y = 9;
		}
	}
	_x = 1;
	_y = 11;
	for (i = 80; i < 108; i++)
	{
		sodwall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = sodwall[i].GetMapTerrain();           //设置地形属性
		++_x;
		if (i == 84 || i == 88 || i == 98||i==102)
			_x += 2;
		else if (i == 93)
		{
			_x = 1;
			_y++;
		}
		else if (i == 99)
			_y -= 4;
		else if (i == 101)
			_y += 4;
	}
	_x = 7;
	_y = 6;
	for (i = 108; i < num_sodwall; i++)
	{
		sodwall[i].SetXY({ _x,_y });                     //设置地形坐标
		MT[_x][_y] = sodwall[i].GetMapTerrain();           //设置地形属性
		++_x;
		if (i == 109)
			_x += 2;
		else if (i == 111)
		{
			_x = 8;
			--_y;
		}
		else if (i == 115)
		{
			_x = 9;
			--_y;
		}
		else if (i == 117)
		{
			_x = 0;
			_y = 8;
		}
		else if (i == 118)
			_x += 18;
	}


}

COORD Map::CreatObjectXY(int h)
{
	COORD _xy;          //要生成的坐标
	int flag;           //用来判断是否生成位置正确
	srand((unsigned int)time(NULL));

	do {
		flag = 0;
		//防止传进来的随机数永远不符合条件，再随机一次
		_xy.X = (rand()+h) % (1100) ;    //1200是地图宽度
		_xy.Y = (rand()+h) % (540) ;     //540为地图上半部分
		_xy.X = (_xy.X / 60) * 60;
		_xy.Y = (_xy.Y / 60) * 60;

		if (!GetTankAdmit(_xy))        //判断坦克是否能到这个位置
			flag = 1;
	} while (flag);
	return _xy;
}

const void Map::PrintMap_1()
{
	int i;
	for ( i = 0; i < num_stee; i++)
		steewall[i].Print();
	for (i = 0; i < num_river; i++)
		river[i].Print();
	for (i = 0; i < num_brush; i++)
		brush[i].Print();
}

const void Map::PrintMap_2()
{
	int i;
	for (i = 0; i < num_sodwall; i++)
		sodwall[i].Print();
	home.Print();
}
