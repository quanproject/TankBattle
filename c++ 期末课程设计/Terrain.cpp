#include "Terrain.h"



Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}




Floor::Floor()
{
	mapterrain.ShellT = 1;
	mapterrain.TankT = 1;
	HP = 1;         //地面不会掉血
}

SteeWall::SteeWall()
{
	mapterrain.ShellT = 0;
	mapterrain.TankT = 0;
	HP = 1000;         //钢铁几乎无法破坏
}

SodWall::SodWall()
{

	mapterrain.ShellT = 0;
	mapterrain.TankT = 0;
	HP = 2;         
}

Brush::Brush()
{
	mapterrain.ShellT = 0;
	mapterrain.TankT = 1;
	HP = 1000;         
}

River::River()
{
	mapterrain.ShellT = 1;
	mapterrain.TankT = 0;
	HP = 1000;        
}

Home::Home()
{
	mapterrain.ShellT = 0;
	mapterrain.TankT = 0;
	HP = 1;
	XY = { 20 * GAMESIZE,26 * GAMESIZE };  //初始坐标
}


void Floor::Print()
{
	IMAGE img1;
	loadimage(&img1, _T("Floor.jpg")); //读取照片 （像素为60x60）
	putimage(XY.X, XY.Y, &img1);
}

void SteeWall::Print()
{
	IMAGE img1;

	loadimage(&img1, _T("SteeWall.jpg")); //读取照片 （像素为60x60）

	putimage(XY.X, XY.Y, &img1);
}

void SodWall::Print()
{
	IMAGE img1;

	if (HP == 2)
		loadimage(&img1, _T("SodWall_intact.jpg")); //读取完好墙的照片 （像素为60x60）
	if (HP == 1)
		loadimage(&img1, _T("SodWall_damage.jpg")); //读取完好墙的照片 （像素为60x60）

	putimage(XY.X, XY.Y, &img1);
}

void Brush::Print()
{
	IMAGE img1;
	loadimage(&img1, _T("Brush.jpg")); //读取照片 （像素为60x60）
	putimage(XY.X, XY.Y, &img1);
}

void River::Print()
{
	IMAGE img1;
	loadimage(&img1, _T("River.jpg")); //读取照片 （像素为60x60）
	putimage(XY.X, XY.Y, &img1);
}

void Home::Print()
{
	IMAGE img1;
	loadimage(&img1, _T("Home.jpg")); //读取照片 （像素为60x60）
	putimage(XY.X, XY.Y, &img1);
}