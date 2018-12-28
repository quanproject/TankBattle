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

}

void Map::ReadyforMap_one()
{

}

void Map::CreatMap_one()
{

}