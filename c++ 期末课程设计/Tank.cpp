#include "Tank.h"
#include"main_game.h"


Tank::Tank()
{
	Speed = SpeedLevel_1;           //初始速度
	Hp = 1;                         //初始生命
	Dir = UP;                       //初始方向
	ReadyForFire = 1;               //开局装弹
	FireInterval = IntervalLevel_1; //初始攻击间隔
}


Tank::~Tank()
{
}


void Tank::ChangeSpeed(int newspeed)
{
	Speed = newspeed;
}

const int Tank::GetSpeed()
{
	return Speed;
}

void Tank::Setxy(COORD xy)
{
	XY = xy;
}

const COORD Tank::Getxy()
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

const int Tank::GetDir()
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
	loadimage(&img1, _T("PlayerTank.jpg")); //读取照片 （像素为60x60）

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

const int Tank::GetFireInterval()
{
	return FireInterval;
}

void Tank::FireIntevalFigure()
{
	static int nowInterval = GetFireInterval();  //初始化冷却时间
	nowInterval--;                   //冷却ing
	if (nowInterval == 0)           //冷却好了
	{
		nowInterval = GetFireInterval();  //重置冷却时间
		ChangeReadyForFire(1);      //装弹（可以射击下一发
	}
}

void Tank::ChangeReadyForFire(int ReadyOrNot)
{
	ReadyForFire = ReadyOrNot;
}

void PlayTank::Fire()
{
	ChangeReadyForFire(0);     //进入开火冷却
	TankShell = new Shell(GetDir(), Getxy());
}

void PlayTank::MoveTank(int NewDir)
{
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
