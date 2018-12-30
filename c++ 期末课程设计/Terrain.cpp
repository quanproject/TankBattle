#include "Terrain.h"



Terrain::Terrain()
{
}


Terrain::~Terrain()
{
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
	Dynamic = 0;
	HP = 1000;        
}

Home::Home()
{
	mapterrain.ShellT = 0;
	mapterrain.TankT = 0;
	HP = 1;
	XY = { 19 * GAMESIZE,24 * GAMESIZE };  //初始坐标
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
		loadimage(&img1, _T("SodWall_damage.jpg")); //读取损坏墙的照片 （像素为60x60）
	if(HP<1)
		loadimage(&img1, _T("SodWall_over.jpg")); //读取废墟墙的照片 （像素为60x60）
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
	Dynamic++;

	if(Dynamic%10<5)       //根据dynamic打印不同图片
	loadimage(&img1, _T("River_0.jpg")); //读取照片 （像素为60x60）
	else
	loadimage(&img1, _T("River_1.jpg")); //读取照片 （像素为60x60）

	putimage(XY.X, XY.Y, &img1);

	if (Dynamic > 10000)         //防止爆炸
		Dynamic = 0;
}

void Home::Print()
{
	IMAGE img1;

	Dynamic++;

	if (Dynamic % 10 < 3)       //根据dynamic打印不同图片
		loadimage(&img1, _T("Home_0.jpg")); //读取照片 （像素为60x60）
	else if(Dynamic % 10 < 5|| Dynamic % 10>7)
		loadimage(&img1, _T("Home_1.jpg")); //读取照片 （像素为60x60）
	else
	loadimage(&img1, _T("Home_2.jpg")); //读取照片 （像素为60x60）

	putimage(XY.X, XY.Y, &img1);

	if (Dynamic > 10000)         //防止爆炸
		Dynamic = 0;
}