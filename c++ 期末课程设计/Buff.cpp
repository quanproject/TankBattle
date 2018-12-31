#include "Buff.h"



Buff::Buff()
{
}


Buff::~Buff()
{
}


void HPBuff::Print()
{
	IMAGE img1;
	Dynamic++;
	int n = Dynamic % 18;

	if (n < 3)
		loadimage(&img1, _T("Buff_Hp_0.jpg")); //读取照片 （像素为60x60）
	else if (n < 6)
		loadimage(&img1, _T("Buff_Hp_1.jpg"));
	else if (n < 9)
		loadimage(&img1, _T("Buff_Hp_2.jpg"));
	else if (n < 12)
		loadimage(&img1, _T("Buff_Hp_3.jpg"));
	else if (n < 15)
		loadimage(&img1, _T("Buff_Hp_1.jpg"));
	else if (n < 18)
		loadimage(&img1, _T("Buff_Hp_0.jpg"));

	if (Dynamic > 10000)
		Dynamic = 0;

	putimage(XY.X, XY.Y, &img1);
}

void FireIntervalBuff::Print()
{
	IMAGE img1;
	Dynamic++;
	int n = Dynamic % 15;

	if (n < 3)
		loadimage(&img1, _T("Buff_Shell_0.jpg")); //读取照片 （像素为60x60）
	else if (n < 6)
		loadimage(&img1, _T("Buff_Shell_1.jpg"));
	else if (n < 9)
		loadimage(&img1, _T("Buff_Shell_2.jpg"));
	else if (n < 12)
		loadimage(&img1, _T("Buff_Shell_1.jpg"));
	else if (n < 15)
		loadimage(&img1, _T("Buff_Shell_0.jpg"));

	if (Dynamic > 10000)
		Dynamic = 0;

	putimage(XY.X, XY.Y, &img1);
}

void MoveSpeedBuff::Print()
{
	IMAGE img1;
	Dynamic++;
	int n = Dynamic % 15;

	if (n < 3)
		loadimage(&img1, _T("Buff_Speed_0.jpg")); //读取照片 （像素为60x60）
	else if (n < 6)
		loadimage(&img1, _T("Buff_Speed_1.jpg"));
	else if (n < 9)
		loadimage(&img1, _T("Buff_Speed_2.jpg"));
	else if (n < 12)
		loadimage(&img1, _T("Buff_Speed_1.jpg"));
	else if (n < 15)
		loadimage(&img1, _T("Buff_Speed_0.jpg"));

	if (Dynamic > 10000)
		Dynamic = 0;

	putimage(XY.X, XY.Y, &img1);
}

void HPBuff::BuffEffect(PlayTank &tank)
{
	tank.ChangeHp(1);
}

void FireIntervalBuff::BuffEffect(PlayTank &tank)
{
	if (tank.GetFireInterval() == IntervalLevel_1)    //1升2，2升3
		tank.ChangeFireInterval(IntervalLevel_2);
	else if(tank.GetFireInterval() == IntervalLevel_2)
		tank.ChangeFireInterval(IntervalLevel_3);
}

void MoveSpeedBuff::BuffEffect(PlayTank &tank)
{
	if (tank.GetSpeed() == SpeedLevel_1)
		tank.ChangeSpeed(SpeedLevel_2);
	else if (tank.GetSpeed()== SpeedLevel_2)
		tank.ChangeSpeed(SpeedLevel_3);
	tank.Setxy({ (tank.Getxy().X / 60) * 60,(tank.Getxy().Y / 60) * 60 });  //防止速度改变造成的卡位
}