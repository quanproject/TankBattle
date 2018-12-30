#include "Shell.h"
#include"main_game.h"

Shell::Shell(Dir facedir, COORD xy)
{
	Direction = facedir;       //获取方向

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

	RectSphere = 10;        //炮弹像素10x10
}

Shell::~Shell()
{

}

void Shell::Print()
{
	IMAGE img1, img2;
	loadimage(&img1, _T("Shell.jpg")); //读取照片 （像素为10x10）

	 //根据方向和位置打印坦克
	if (Direction == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印炮弹
	}
	else if (Direction == DOWN)
	{
		// 旋转图像 180 度 (PI / 6)
		rotateimage(&img2, &img1, PI);

		putimage(XY.X, XY.Y, &img2);

	}
	else if (Direction == LEFT)
	{
		// 旋转图像 270 度 (PI / 6)
		rotateimage(&img2, &img1, PI / 2);

		putimage(XY.X, XY.Y, &img2);

	}
	else
	{
		// 旋转图像 30 度 (PI / 6)
		rotateimage(&img2, &img1, (3 * PI) / 2);

		putimage(XY.X, XY.Y, &img2);

	}
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

COORD Shell::GetXY()
{
	return XY;
}

void Shell::PrintShellBoom()
{
	IMAGE img;
	loadimage(&img, _T("Boom.jpg"));
	putimage(XY.X-10, XY.Y-10, &img);
}