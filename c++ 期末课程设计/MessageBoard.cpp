#include "MessageBoard.h"



MessageBoard::MessageBoard()
{
	Speed = SpeedLevel_1;           //初始速度
	Hp = 2;                         //初始生命
	FireInterval = IntervalLevel_1; //初始攻击间隔
	card = 1;                       //第一关
	XY = { 0,810 };
}


MessageBoard::~MessageBoard()
{
}

const void MessageBoard::Print()
{
	IMAGE img1;
	loadimage(&img1, _T("MessageBoard.jpg")); //读取照片 （像素为60x60）
	putimage(XY.X, XY.Y, &img1);

	//打印血量
	setbkcolor(BLACK);              //设置字体背景颜色
	settextstyle(30, 0, _T("黑体"));   //设置文字格式各个参数
	settextcolor(RED);          //字体颜色
	if(Hp==1)
		outtextxy(150,840, _T("1"));
	else if(Hp==2)
		outtextxy(150, 840, _T("2"));
	else if(Hp==3)
		outtextxy(150, 840, _T("3"));
	else
		outtextxy(150, 840, _T("0"));

	settextcolor(GREEN);          //字体颜色
	//打印关卡
	if (card == 1)
		outtextxy(900, 840, _T("第 一 关"));
	else if (card==2)
		outtextxy(900, 840, _T("第 二 关"));

	settextstyle(20, 0, _T("黑体"));   //设置文字格式各个参数
	//打印速度
	if (Speed == SpeedLevel_1)
		outtextxy(300, 825, _T("Level 1"));
	else if (Speed == SpeedLevel_2)
		outtextxy(300, 825, _T("Level 2"));
	else if (Speed == SpeedLevel_3)
		outtextxy(300, 825, _T("Level 3"));
	else;

	//打印火力
	if (FireInterval == IntervalLevel_1)
		outtextxy(300, 855, _T("Level 1"));
	else if (FireInterval == IntervalLevel_1)
		outtextxy(300, 855, _T("Level 2"));
	else if (FireInterval == IntervalLevel_1)
		outtextxy(300, 855, _T("Level 3"));
	else;



}

void MessageBoard::ChangeTankMessage(PlayTank tank)
{
	Speed = tank.GetSpeed();
	Hp = tank.GetHP();
	FireInterval = tank.GetFireInterval();
}
