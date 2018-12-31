#include "Tank.h"
#include"main_game.h"
using namespace std;

//list<Shell*> EnemyTankShell;          //储存敌方坦克的子弹

Tank::Tank()
{

}


Tank::~Tank()
{
}


void Tank:: ChangeHp(int flag)
{
	if (flag == 1) //根据情况加减生命值
		Hp++;
	if (flag == 0)
		Hp--;
}

const void Tank::TankBoom()
{
	IMAGE img;
	loadimage(&img, _T("Boom.jpg"));
	putimage(XY.X , XY.Y , &img);
}

void Tank::FireIntevalFigure()
{
	if(!ReadyForFire)   //如果并没有冷却好，才开始减冷却
	nowInterval--;                   //冷却ing
	if (nowInterval <= 0)           //冷却好了
	{
		nowInterval = FireInterval;  //重置冷却时间
		ReadyForFire=1;      //装弹（可以射击下一发
	}
}

//////////////////////////////////////玩家tank////////////////////////////////
PlayTank::PlayTank()
{
	Speed = SpeedLevel_1;           //初始速度
	Hp = 2;                         //初始生命
	Direction = UP;                 //初始方向
	ReadyForFire = 1;               //开局装弹
	FireInterval = IntervalLevel_1; //初始攻击间隔
	RectSphere = 60;                //坦克大小60x60像素
	nowInterval = FireInterval;  //初始化冷却时间
}

void PlayTank::Fire()
{
	ReadyForFire=0;     //进入开火冷却
}

void PlayTank::MoveTank(Dir NewDir)
{
			switch (NewDir) {    //按照移动速度移动
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
				XY.X+= Speed;
				break;
			}
}

void PlayTank::Print()
{
	IMAGE img1,img2;
	loadimage(&img1, _T("PlayerTank.jpg")); //读取照片 （像素为60x60）

     //根据方向和位置打印坦克
	if (Direction == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印坦克
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
		rotateimage(&img2, &img1, (3*PI) / 2);

		putimage(XY.X, XY.Y, &img2);

	}
}

/////////////////////////////////////普通敌方坦克//////////////////////////
NormalAITank::NormalAITank()
{
	Speed = SpeedLevel_1;           //初始速度
	Hp = 2;                         //初始生命
	Direction = DOWN;                 //初始方向
	ReadyForFire = 0;               //开局装弹
	FireInterval = IntervalLevel_1; //初始攻击间隔
	RectSphere = 60;                //坦克大小60x60像素
}

void NormalAITank::Print()
{
	IMAGE img1, img2;
	loadimage(&img1, _T("NormalTank.jpg")); //读取照片 （像素为60x60）

	 //根据方向和位置打印坦克
	if (Direction == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印坦克
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

Dir NormalAITank::NormalMoveAI(int h)
{

	int n = h % 15;
	if (n < 11)
		return Direction;  //大多情况下保持原方向不变
	else if (n < 12)
		return UP;
	else if (n < 13)
		return DOWN;
	else if (n < 14)
		return LEFT;
	else
		return RIGHT;
}

void NormalAITank::MoveTank(Dir NewDir)
{
		switch (NewDir) {    //按照移动速度移动
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
		}
}

/*
void NormalAITank::Fire()
{
	ReadyForFire = 0;
	Shell *p = new Shell(Direction,XY);   //申请新内存
	p->Print();
	EnemyTankShell.push_back(p);                       //压入炮弹容器
}
*/

////////////////////////////////////精英敌方坦克//////////////////////////
BossAITank::BossAITank()
{
	Speed = SpeedLevel_3;           //初始速度
	Hp = 3;                         //初始生命
	Direction = UP;                 //初始方向
	ReadyForFire = 1;               //开局装弹
	FireInterval = IntervalLevel_3; //初始攻击间隔
	RectSphere = 60;                //坦克大小60x60像素
}

void BossAITank::Print()
{
	IMAGE img1, img2;
	loadimage(&img1, _T("BossTank.jpg")); //读取照片 （像素为60x60）

	 //根据方向和位置打印坦克
	if (Direction == UP)
	{
		putimage(XY.X, XY.Y, &img1);       //在固定位置打印坦克
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

Dir BossAITank::BossMoveAI(int h)
{
	int n = h % 15;
	if (XY.Y < 400)       //在地图上半部分
	{
		if (n < 8)
			return Direction;  //大多情况下保持原方向不变
		else if (n < 12)
			return DOWN;        //更趋于向下走
		else if (n < 13)
			return LEFT;
		else
			return RIGHT;
	}
	else
	{
		if (n < 11)
			return Direction;  //大多情况下保持原方向不变
		else if (n < 12)
			return UP;         //任意方向走
		else if (n < 13)
			return DOWN;
		else if (n < 14)
			return LEFT;
		else
			return RIGHT;
	}
}

void BossAITank::MoveTank(Dir NewDir)
{
	switch (NewDir) {    //按照移动速度移动
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
	}
}