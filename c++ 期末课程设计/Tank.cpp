#include "Tank.h"
#include"main_game.h"


Tank::Tank()
{
	Speed = 15;
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

void Tank::ChangeSpeed(int newspeed)
{
	Speed = newspeed;
}

int Tank::GetSpeed()
{
	return Speed;
}

void Tank::Setxy(COORD xy)
{
	XY = xy;
}

COORD Tank::Getxy()
{
	return XY;
}

void Tank:: ChangeHp(int flag)
{
	if (flag == 1) //根据情况加减生命值
		Hp++;
	if (flag == 0)
		Hp--;

}

void Tank::ChangeDir(int newdir)
{
	Dir = newdir;
}

int Tank::GetDir()
{
	return Dir;
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
		int NewDir = _getch();  //获取方向
		if (NewDir == UP || NewDir == DOWN || NewDir == RIGHT || NewDir == LEFT)       //判断是否为方向操作
		{
			COORD oldxy = Getxy();    //获取坐标
			short speed = GetSpeed(); //获取速度
			ChangeDir(NewDir);
			switch (NewDir) {    //按照移动速度移动
			case UP:
				Setxy({ oldxy.X,oldxy.Y - speed });  //修改坐标
				break;
			case DOWN:
				Setxy({ oldxy.X,oldxy.Y + speed });
				break;
			case LEFT:
				Setxy({ oldxy.X - speed,oldxy.Y });
				break;
			case RIGHT:
				Setxy({ oldxy.X + speed,oldxy.Y });
				break;
			}
		}
	}
}
