#include"main_game.h"      //游戏主要数据头文件
#include"Buff.h"           //buff类
#include"Tank.h"           //坦克类
#include"TankGameMenu.h"   //游戏菜单类
#include"Terrain.h"        //地形类
using namespace std;

//画正方形
void const drawdre(COORD x)
{
	solidrectangle(x.X*GAMESIZE, x.Y* GAMESIZE, x.X*GAMESIZE + GAMESIZE, x.Y* GAMESIZE + GAMESIZE); //30x30的正方形
}

//坐标比较函数
int const cor_cmp(COORD pt1, COORD pt2)
{
	return (pt1.X == pt2.X&&pt1.Y == pt2.Y); //相等便返回1
}



//++++++++++++++++++++++++++++++++++++++++++++主函数+++++++++++++++++++++++++++++++++++++++++++++//
int main()
{
	TankGameMenu GAME;
	GAME.printTankGameMenu();




	cout << "success！" << endl;
	system("pause");
	return 0;
}
