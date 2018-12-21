#include "TankGameMenu.h"

void const drawdre(COORD x);            //声明画方块函数

TankGameMenu::TankGameMenu()
{
}


TankGameMenu::~TankGameMenu()
{
}
//主菜单
void TankGameMenu::printTankGameMenu()
{
	initgraph(1200, 900);              //初始化图形界面
	setbkcolor(BLACK);              //设置字体背景颜色
	setfillcolor(BLACK);            //设置初始背景颜色
	solidrectangle(0,0,1200,900);      //画出背景色
	settextstyle(40, 0, _T("黑体"));   //设置文字格式各个参数

	int const ox = 500;          //标注位置的常量

	settextcolor(RED);          //被选择的字体颜色
	outtextxy(ox, ox-100, _T("游 戏 开 始"));//菜单界面文字输出
	settextcolor(GREEN);        //未选择的字体颜色
	outtextxy(ox, ox+50, _T("游 戏 说 明"));
	outtextxy(ox, ox+200, _T("退 出 游 戏"));

	int dir;                        //菜单选择方向，上和下
	int flag = 1;                   //确定选择
	while (1)
	{
		if (_kbhit())
		{//根据flag值进行移动

			dir = _getch();    //获取方向键值
			if (dir == UP && flag != 1)  //根据键值变换选项
				flag--;
			if (dir == DOWN && flag != 3)
				flag++;
			if (dir == DETER)
				break;
			settextcolor(GREEN);
			outtextxy(ox, ox-100, _T("游 戏 开 始"));//菜单界面文字颜色覆盖
			outtextxy(ox, ox+50, _T("游 戏 说 明"));
			outtextxy(ox, ox+200, _T("退 出 游 戏"));

			switch (flag)                //根据选项变换颜色
			{
			case 1: settextcolor(RED);
				outtextxy(ox, ox - 100, _T("游 戏 开 始"));
				break;
			case 2: settextcolor(RED);
				outtextxy(ox, ox + 50, _T("游 戏 说 明"));
				break;
			case 3:settextcolor(RED);
				outtextxy(ox, ox + 200, _T("退 出 游 戏"));
				break;
			default: break;
			}
		}
	}
	if (flag == 1)//游戏开始
	{
		GameStart(1);
	}
	if (flag == 2)//游戏说明
	{
		Commeting();
	}
	if (flag == 3)//退出游戏
	{
		Inaugurated();  //结束动画
		exit(-1);
	}

}
//刷屏
void TankGameMenu::Inaugurated()
{
	setfillcolor(GREEN);            //设置颜色
	COORD point = { 0,0 };          //设置笔尖位置（画方块的初始位置
	while (point.Y<=2)
	{
		while (point.X <= 60)
		{
			drawdre(point);
			drawdre({ point.X-7,point.Y + 1 });
			drawdre({ point.X-15,point.Y + 2 });
			drawdre({ point.X-2,point.Y + 4 });
			drawdre({ point.X-1,point.Y + 5 });
			drawdre({ point.X-4,point.Y + 6 });
			drawdre({ point.X - 15,point.Y + 8 });
			drawdre({ point.X-1,point.Y + 9 });
			drawdre({ point.X-2,point.Y + 11 });
			drawdre({ point.X - 3,point.Y + 13 });
			drawdre({ point.X - 15,point.Y + 15 });
			drawdre({ point.X - 6,point.Y + 16 });
			drawdre({ point.X - 7,point.Y + 18 });
			drawdre({ point.X - 18,point.Y + 20 });
			drawdre({ point.X - 1,point.Y + 21 });
			drawdre({ point.X - 18,point.Y + 23 });
			drawdre({ point.X - 15,point.Y + 24 });
			drawdre({ point.X - 1,point.Y + 26 });
			drawdre({ point.X - 4,point.Y + 28 });
			drawdre({ point.X - 1,point.Y + 30 });
			drawdre({ point.X - 20,point.Y + 32 });
			drawdre({ point.X - 15,point.Y + 33 });
			drawdre({ point.X - 4,point.Y + 35 });
			drawdre({ point.X - 1,point.Y + 37 });
			drawdre({ point.X - 20,point.Y + 39 });
			drawdre({ point.X - 4,point.Y + 40 });
			point.X += 1;
			Sleep(8);
		}
		point.X = 0;
		point.Y += 1;
	}
	printf("%d,%d\n", point.X, point.Y);
}
//游戏开始
void TankGameMenu::GameStart(int card)
{
	setfillcolor(BLACK);            //设置初始背景颜色
	solidrectangle(0, 0, 1200, 900);      //画出背景色



	/////////////////////////////////////////////////////////////////测试范围//////////////////////////////////////////////////
	//定义多个对象
	PlayTank player;
	player.Setxy({ 0,0 });              //定位玩家初始坐标
	player.PrintTank();                //打印玩家坦克
	int operation;                    //记录操作键
	//画地图Map类（根据card确定map
	//循环游戏过程
	BeginBatchDraw();
	while (1)
	{
		if (_kbhit())       //如果有输入
		{
			operation= _getch();    //获取当前操作
			if (operation == DETER)
			{

			}
			if(operation == UP || operation == DOWN || operation == RIGHT || operation == LEFT)
				player.MoveTank(operation);      //移动坦克
			//玩家操作
			//坦克移动（玩家+ai
		}
		player.PrintTank();
		//炮弹移动
		//结算
		//玩家生存状况（跳出
		//通关判定（跳出并调用下一关
		FlushBatchDraw();
		Sleep(30); //游戏延迟
		cleardevice();
	}
	EndBatchDraw();
	//死亡界面
	//再来一局or返回界面


	//////////////////////////////////////////////////////////////////测试范围/////////////////////////////////////////////////////////
}
//游戏说明
void TankGameMenu::Commeting()
{
	//打印一张图片
	loadimage(NULL, _T("说明图片"));
	//按k返回
	int flag;     //判断输入
	if (_kbhit())
		flag=_getch();
	if (flag == ACT)
		printTankGameMenu(); //返回选择菜单
}