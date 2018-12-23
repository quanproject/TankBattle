#include "Shell.h"
#include"main_game.h"

Shell::Shell(int dir, COORD xy)
{
	Direction = dir;       //获取方向

	if (Direction == UP)   //炮弹的初始位置应该在坦克的正面前方
	{
		XY.X = xy.X+25 ;
		XY.Y = xy.Y - 10;
	}
	else if (Direction == DOWN)
	{
		XY.X = xy.X + 25;
		XY.Y = xy.Y + 60;
	}
	else if (Direction == LEFT)
	{
		XY.X = xy.X - 10;
		XY.Y = xy.Y + 25;
	}
	else  //RIGHT
	{
		XY.X = xy.X + 60;
		XY.Y = xy.Y +25;
	}
}

Shell::~Shell()
{

}

void Shell::Print()
{
	IMAGE img1;
	loadimage(&img1, _T("Shell.jpg")); //读取照片 (像素为10x10）
	putimage(XY.X, XY.Y, &img1);       //在固定位置打印炮弹
}

void Shell::Fly()
{
	if (Direction == UP)                           //判断炮弹飞行方向并改变坐标
		XY.Y -= ShellFlySpeed;
	else if (Direction == DOWN)
		XY.Y += ShellFlySpeed;
	else if (Direction == LEFT)
		XY.X -= ShellFlySpeed;
	else  //RIGHT
		XY.X += ShellFlySpeed;
}

const COORD Shell::GetShellxy()
{
	return XY;
}