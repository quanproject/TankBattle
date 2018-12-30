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
bool const cor_cmp(COORD pt1, COORD pt2)
{
	return (pt1.X == pt2.X&&pt1.Y == pt2.Y); //相等便返回1
}

//炮弹命中坦克返回1
bool const JudgmentKill(COORD shellxy, COORD tankxy)
{
	if (shellxy.X > tankxy.X
		&&shellxy.X<tankxy.X + 60
		&& shellxy.Y>tankxy.Y
		&&shellxy.Y<tankxy.Y + 60
		&& shellxy.X + 10>tankxy.X
		&&shellxy.X + 10 < tankxy.X + 60
		&& shellxy.Y + 10 > tankxy.Y
		&&shellxy.Y + 10 < tankxy.Y + 60
		)
		return 1;
	return 0;

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
