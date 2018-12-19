#include "Tank.h"
#include"main_game.h"


Tank::Tank()
{
	Speed = 6;
	Hp = 1;
	Dir = UP;
}


Tank::~Tank()
{
}

void Tank::MoveTank()
{
	if (_kbhit())       //如果有输入
	{
		Dir = _getch();  //获取方向
		switch (Dir) {    //按照移动速度移动
		case UP:
			XY.Y -= Speed;  //修改坐标
			break;
		case DOWN:
			XY.Y += Speed;
			break;
		case LEFT:
			XY.X -= Speed;
			break;
		case RIGHT:
			XY.X += Speed;
			break;
		case 0:
			break;
		}
	}
}

void Tank::ChangSpeed(int newspeed)
{
	Speed = newspeed;
}

void Tank::Setxy(COORD xy)
{
	XY = xy;
}

void Tank:: ChangHp(int flag)
{
	if (flag == 1) //根据情况加减生命值
		Hp++;
	if (flag == 0)
		Hp--;

}

void Tank::ChangeFireInterval(int NewInterval)
{
	FireInterval = NewInterval;
}

void Tank::PrintTank()
{
	IMAGE img1,img2;
	loadimage(&img1, _T("PlayerTank.jpg")); //读取照片

     //根据方向和位置打印坦克
	if (Dir == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印坦克
	}
	else if (Dir == DOWN)
	{
		// 旋转图像 180 度 (PI / 6)
		rotateimage(&img2, &img1, PI);

		putimage(XY.X, XY.Y, &img2);

	}
	else if (Dir == LEFT)
	{
		// 旋转图像 270 度 (PI / 6)
		rotateimage(&img2, &img1, PI / 2);

		putimage(XY.X, XY.Y, &img2);

	}
	else
	{
		// 旋转图像 30 度 (PI / 6)
		rotateimage(&img2, &img1, (3*PI) / 2);

		putimage(XY.X, XY.Y, &img2);

	}
}

/*
void PlayTank::Fire()
{
	if (_kbhit())       //如果有输入
	{

	}
	//考虑攻击间隔
}

void PlayTank::MoveTank()
{
	if (_kbhit())       //如果有输入
	{
		Dir = _getch();  //获取方向
		switch (Dir) {    //按照移动速度移动
		case UP:
			XY.Y -= Speed;  //修改坐标
			break;
		case DOWN:
			XY.Y += Speed;
			break;
		case LEFT:
			XY.X -= Speed;
			break;
		case RIGHT:
			XY.X += Speed;
			break;
		case 0:
			break;
		}
	}
}
*/