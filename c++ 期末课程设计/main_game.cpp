#include"main_game.h"      //游戏主要数据头文件
#include"Buff.h"           //buff类
#include"Tank.h"           //坦克类
#include"TankGameMenu.h"   //游戏菜单类
#include"Terrain.h"        //地形类
using namespace std;

//容器
list<Shell*> PlayerTankShell;         //存储玩家坦克的子弹 
list<Shell*> EnemyTankShell;          //储存敌方坦克的子弹
list<NormalAITank*> NormalTank;       //储存敌方坦克


//迭代器
list<Shell*>::iterator PTS;           //玩家坦克的子弹
list<Shell*>::iterator ETS;           //敌方坦克的子弹
list<NormalAITank*>::iterator NT;     //敌方坦克
list<NormalAITank*>::iterator _NT;     //敌方坦克（用于嵌套遍历查找坦克碰撞


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
	if ((shellxy.X > tankxy.X
		&&shellxy.X<tankxy.X + 60
		&& shellxy.Y>tankxy.Y
		&&shellxy.Y<tankxy.Y + 60
		)||( shellxy.X + 10>tankxy.X
		&&shellxy.X + 10 < tankxy.X + 60
		&& shellxy.Y + 10 > tankxy.Y
		&&shellxy.Y + 10 < tankxy.Y + 60
		))
		return 1;
	return 0;

}

//判断是否跟敌方坦克碰撞
bool const JudgmentTankCollision(COORD Tankxy,COORD m_xy)
{
	for (_NT = NormalTank.begin(); _NT != NormalTank.end();_NT++)
	{
		COORD otherTank = (*_NT)->Getxy();
		
		if (cor_cmp(otherTank, m_xy))  //跳过自己
			;
		else if(Tankxy.X>otherTank.X-60&&Tankxy.X<otherTank.X+60
			&& Tankxy.Y>otherTank.Y - 60 && Tankxy.Y < otherTank.Y + 60)
		{
			return 1;
			break;
		}
	}
	return 0;
}

//判断是否跟玩家坦克碰撞
bool const JudgmentCollisionPlayer(COORD Tankxy,COORD player)
{
	if (Tankxy.X > player.X - 60 && Tankxy.X<player.X + 60
		&& Tankxy.Y>player.Y - 60 && Tankxy.Y < player.Y + 60)
		return 1;
	return 0;
}

//判断玩家炮弹是否与敌方炮弹碰撞
bool const JudgmentShellCollision(COORD shellxy)
{
	for (ETS = EnemyTankShell.begin(); ETS != EnemyTankShell.end();ETS++)
		if (  (*ETS)->GetXY().X  > shellxy.X-10 && (*ETS)->GetXY().X< shellxy.X + 10
			&& (*ETS)->GetXY().Y  > shellxy.Y - 10 && (*ETS)->GetXY().Y < shellxy.Y + 10
			)
		{
			EnemyTankShell.erase(ETS);
			return 1;
				break;
		}
	return 0;
}


//++++++++++++++++++++++++++++++++++++++++++++主函数+++++++++++++++++++++++++++++++++++++++++++++//
int main()
{
	TankGameMenu GAME;
	GAME.printTankGameMenu();


	setfillcolor(BLACK);            //设置初始背景颜色
	solidrectangle(0, 0, 1200, 900);      //画出背景色

	srand((unsigned int)time(NULL));

	////////////////////////////////////////////////////测试范围//////////////////////////////////////////////////
	//定义多个对象


	COORD Judgmentxy;                   //用来判断是否遇到地形阻挡的 坐标记录
	Map gamemap;                        //定义地图
	int operation;                    //记录操作键
	int random;                       //一个随机数
	int card=1;                         //选关






	while (card<5)  //最多做五关（
	{
		PlayTank player;                    //定义玩家坦克
		player.Setxy({ 14 * GAMESIZE,24 * GAMESIZE });              //定位玩家初始坐标
		//根据选择生成不同的关
		if (card == 1)
		{
			gamemap.ReadyforMap_one();            //地图生成第一关
			//生成整个背景
			loadimage(NULL, _T("Floor.jpg"));          //背景地图
			gamemap.PrintMap_1();
			gamemap.PrintMap_2();			
			Sleep(1000);
			//画标题，做为入场
			IMAGE img1;
			loadimage(&img1, _T("chapter_1.jpg"));     //读取照片
			putimage(0,300, &img1);
			Sleep(3000);
		}
		else if (card == 2)
		{
			//地图生成第二关
		}

		BeginBatchDraw();          //开始批量绘图
		//循环游戏过程
		while (1)
		{

			//玩家按键操作响应
			if (_kbhit())       //如果玩家有输入
			{
				operation = _getch();    //获取当前操作

				if (operation == DETER && player.GetReadyForFire())          //确认攻击操作而且已经冷却好了
				{
					player.Fire();             //使玩家进入开炮冷却
					Shell *p = new Shell(player.GetDir(), player.Getxy());   //申请新内存
					p->Print();                                          //打印炮弹
					PlayerTankShell.push_back(p);                       //压入炮弹容器
				}

				else if (operation == UP || operation == DOWN || operation == RIGHT || operation == LEFT)    //移动操作
				{
					Judgmentxy = player.Getxy();   //记录当前坦克坐标
					player.ChangeDir((Dir)operation);           //修改坦克朝向
					switch (operation) {
					case UP:
						Judgmentxy.Y -= player.GetSpeed();
						break;
					case DOWN:
						Judgmentxy.Y += player.GetSpeed();
						break;
					case LEFT:
						Judgmentxy.X -= player.GetSpeed();
						break;
					case RIGHT:
						Judgmentxy.X += player.GetSpeed();
						break;
					}
					if (gamemap.GetTankAdmit(Judgmentxy)                                  //判断四角是否与地形碰撞
						&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
						&& gamemap.GetTankAdmit({ Judgmentxy.X ,Judgmentxy.Y + 59 })
						&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y })
						&& !gamemap.JudgmentBorder(Judgmentxy)                             //判断两角是否超界
						&& !gamemap.JudgmentBorder({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
						&&!JudgmentTankCollision(Judgmentxy,player.Getxy()))
						player.MoveTank((Dir)operation);      //移动坦克        这里将int型强制转换为Dir（方向）类型
				}
				//玩家操作
			}

			//生成敌方坦克	
			if (gamemap.GetNumNormalTank() > 0 && NormalTank.size() < 3)   //场上少于3个敌方坦克且坦克还有剩余
			{
				NormalAITank *p = new NormalAITank();        //分配tank内存
				gamemap.KillNormalTank();                  //减少剩余敌方坦克数量
				random = rand();     //随机数
				p->Setxy(gamemap.CreatObjectXY(random));         //随机分配位置
				NormalTank.push_back(p);          //压入
			}

			///////////////////////////////////打印环节//////////////////////////////////////
			loadimage(NULL, _T("Floor.jpg"));          //背景地图
			gamemap.PrintMap_2();   //画地图Map类（根据card确定map  坦克下方
			player.Print();  //打印玩家坦克

			 //对所有普通敌方坦克操作（开火，移动，打印
			for (NT = NormalTank.begin(); NT != NormalTank.end();)
			{
				if ((*NT)->GetHP() == 0)        //判断是否死亡
				{
					NT = NormalTank.erase(NT);       //释放敌方坦克内存
				}
				else
				{
					random = rand();  //随机数
					Dir movedir = (*NT)->NormalMoveAI(random);    //调用普通坦克移动ai
					Judgmentxy = (*NT)->Getxy();        //记录当前坦克坐标


					//开火判断（好了就打
					if ((*NT)->GetReadyForFire())
					{
						(*NT)->ChangeReadyForFire(0);     //冷却
						Shell *p = new Shell(movedir, Judgmentxy);   //申请新内存
						p->Print();
						EnemyTankShell.push_back(p);                       //压入炮弹容器
					}



					//修改坦克朝向
					(*NT)->ChangeDir(movedir);
					switch (movedir) {
					case UP:
						Judgmentxy.Y -= SpeedLevel_1;
						break;
					case DOWN:
						Judgmentxy.Y += SpeedLevel_1;
						break;
					case LEFT:
						Judgmentxy.X -= SpeedLevel_1;
						break;
					case RIGHT:
						Judgmentxy.X += SpeedLevel_1;
						break;
					}

					if (gamemap.GetTankAdmit(Judgmentxy)                                  //判断四角是否与地形碰撞
						&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
						&& gamemap.GetTankAdmit({ Judgmentxy.X ,Judgmentxy.Y + 59 })
						&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y })
						&& !gamemap.JudgmentBorder(Judgmentxy)                             //判断两角是否超界
						&& !gamemap.JudgmentBorder({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
						&&!JudgmentTankCollision(Judgmentxy,(*NT)->Getxy())    //判断是否跟敌方坦克碰撞
						&&!JudgmentCollisionPlayer(Judgmentxy,player.Getxy())  //判断是否跟玩家坦克相撞
						)        
						(*NT)->MoveTank(movedir);      //移动敌方普通坦克        

					(*NT)->Print();         //打印坦克


					++NT;           //对下一个坦克操作
				}
			}
			gamemap.PrintMap_1();  //画地图Map类（根据card确定map   坦克上方


			//迭代器遍历对玩家炮弹操作
			for (PTS = PlayerTankShell.begin(); PTS != PlayerTankShell.end();)
			{

				(*PTS)->Print();       //打印炮弹
				(*PTS)->Fly();         //炮弹移动
				COORD Shellxy = (*PTS)->GetXY();  //记录炮弹坐标
				bool flag = 0;        //是否命中敌方坦克的标志

				for (NT = NormalTank.begin(); NT != NormalTank.end(); NT++)      //遍历坦克来确认有没有命中
				{
					if (JudgmentKill(Shellxy, (*NT)->Getxy()))  //命中
					{
						(*NT)->ChangeHp(0);              //减少HP
						flag = 1;
						break;
					}
				}

				if (!gamemap.GetShellAdmit((*PTS)->GetXY()))			          //判断是否打到地形
				{
					gamemap.ChangeMap((*PTS)->GetXY()); //修改地图（减少墙体耐久
					(*PTS)->PrintShellBoom();
					PTS = PlayerTankShell.erase(PTS);	//命中删除并释放内存
				}
				else if (JudgmentShellCollision((*PTS)->GetXY()))         //炮弹对撞
				{
					(*PTS)->PrintShellBoom();
					PTS = PlayerTankShell.erase(PTS);	//删除并释放内存
				}
				else if (gamemap.JudgmentBorder((*PTS)->GetXY()) || flag)          //炮弹超界或击杀
				{
					(*PTS)->PrintShellBoom();
					PTS = PlayerTankShell.erase(PTS);	//删除并释放内存
				}
				else             //处理下一棵炮弹
				{
					++PTS;
				}
			}

			//迭代器遍历对敌方炮弹操作
			for (ETS = EnemyTankShell.begin(); ETS != EnemyTankShell.end();)
			{

				(*ETS)->Print();       //打印炮弹
				(*ETS)->Fly();         //炮弹移动

				if (!gamemap.GetShellAdmit((*ETS)->GetXY()))			          //判断是否打到地形
				{
					gamemap.ChangeMap((*ETS)->GetXY()); //修改地图（减少墙体耐久
					ETS = EnemyTankShell.erase(ETS);	//命中删除并释放内存
				}
				else if (gamemap.JudgmentBorder((*ETS)->GetXY()))          //炮弹超界
				{

				}
				else if (JudgmentKill((*ETS)->GetXY(), player.Getxy()))      //命中玩家
				{
					player.ChangeHp(0);      //失去HP
					ETS = EnemyTankShell.erase(ETS);	//删除并释放内存
				}
				else             //处理下一棵炮弹
					++ETS;
			}

			player.FireIntevalFigure();          //计算玩家开火冷却缩减
			for (NT = NormalTank.begin(); NT != NormalTank.end(); NT++)
				(*NT)->FireIntevalFigure();      //计算敌方炮弹冷却

			//玩家生存状况（跳出
			if (player.GetHP() == 0)  //玩家生命值归零
				break;

			//通关判定（跳出并调用下一关

			FlushBatchDraw();  //批量绘图
			Sleep(GameSpeed); //游戏延迟
	//		cleardevice();    //清除屏幕
		}
		EndBatchDraw();         //结束批量绘图
		gamemap.CloseMap();     //释放地图内存
		PlayerTankShell.clear();  //清空所有容器
		EnemyTankShell.clear();
		NormalTank.clear();



		//根据血量判断
		if (player.GetHP() == 0)
			GAME.GameOver();    //重新开始/退出
		else
			card++;     //进入下一关
	}



	//////////////////////////////////////////////////////////////////测试范围/////////////////////////////////////////////////////////

	return 0;
}


//buff类
//信息版类

//爆炸效果实现
//精英坦克实装
//第二张地图

//炮弹碰撞bug
//敌方生成卡位bug
