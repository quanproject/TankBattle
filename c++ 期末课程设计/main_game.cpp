﻿#include"main_game.h"      //游戏主要数据头文件
#include"Buff.h"           //buff类
#include"Tank.h"           //坦克类
#include"TankGameMenu.h"   //游戏菜单类
#include"Terrain.h"        //地形类
#include"MessageBoard.h"   //信息板类
#pragma comment(lib,"Winmm.lib")  //bgm库

using namespace std;

list<Shell*> PlayerTankShell;         //存储玩家坦克的子弹 
list<Shell*> EnemyTankShell;          //储存敌方坦克的子弹
list<NormalAITank*> NormalTank;       //储存普通敌方坦克
list<BossAITank*>BossTank;            //储存精英敌方坦克
list<Buff*>AllBuff;                   //储存buff


list<Shell*>::iterator PTS;           //玩家坦克的子弹
list<Shell*>::iterator ETS;           //敌方坦克的子弹
list<NormalAITank*>::iterator NT;     //普通敌方坦克
list<NormalAITank*>::iterator _NT;     //普通敌方坦克（用于嵌套遍历查找坦克碰撞
list<BossAITank*>::iterator BT;       //精英敌方坦克
list<BossAITank*>::iterator _BT;
list<Buff*>::iterator Bf;              //buff

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
bool const JudgmentShellCollision(COORD shellxy,Dir shelldir)
{
	if (shelldir == UP || shelldir == DOWN)
	{
		for (ETS = EnemyTankShell.begin(); ETS != EnemyTankShell.end(); ETS++)  //遍历敌方炮弹
			if ((*ETS)->GetXY().X > shellxy.X - 10 && (*ETS)->GetXY().X< shellxy.X + 10
				&& (*ETS)->GetXY().Y  > shellxy.Y - 10- ShellFlySpeed && (*ETS)->GetXY().Y < shellxy.Y + 10+ ShellFlySpeed       
				)                       // ShellFlySpeed 防止炮弹速度过快而无法相撞
			{
				EnemyTankShell.erase(ETS);         //释放敌方炮弹
				return 1;
				break;
			}
		return 0;
	}
	else  //左右碰撞
	{
		for (ETS = EnemyTankShell.begin(); ETS != EnemyTankShell.end(); ETS++)  //遍历敌方炮弹
			if ((*ETS)->GetXY().X > shellxy.X - 10 - ShellFlySpeed && (*ETS)->GetXY().X< shellxy.X + 10 + ShellFlySpeed
				&& (*ETS)->GetXY().Y  > shellxy.Y - 10 && (*ETS)->GetXY().Y < shellxy.Y + 10
				)
			{
				EnemyTankShell.erase(ETS);         //释放敌方炮弹
				return 1;
				break;
			}
		return 0;
	}
}


//++++++++++++++++++++++++++++++++++++++++++++主函数+++++++++++++++++++++++++++++++++++++++++++++//
int main()
{
	TankGameMenu GAME;
	mciSendString("open start.mp3 alias StartMusic", NULL, 0, NULL);  	// 打开音乐文件
	mciSendString("play StartMusic", NULL, 0, NULL);  //播放音乐
	GAME.printTankGameMenu();
	mciSendString("stop StartMusic", NULL, 0, NULL);  //停止播放并关闭startBGM
	mciSendString("close StartMusic", NULL, 0, NULL);


	setfillcolor(BLACK);            //设置初始背景颜色
	solidrectangle(0, 0, 1200, 900);      //画出背景色

	srand((unsigned int)time(NULL));


	//定义多个对象


	COORD Judgmentxy;                   //用来判断是否遇到地形阻挡的 坐标记录
	Map gamemap;                        //定义地图
	int operation;                    //记录操作键
	int random;                       //一个随机数
	int card=1;                         //选关







	while (card<5)  //最多做五关（
	{
		PlayTank player;                       //定义玩家坦克
		MessageBoard messageboard;             //定义信息板
		int time = 0;                          //时间标值，用于生成buff
		player.Setxy({ 14 * GAMESIZE,24 * GAMESIZE });              //定位玩家初始坐标
		messageboard.ChangeCard(card);                              // 信息板录入关卡
		//根据选择生成不同的关
		if (card == 1)
		{
			gamemap.ReadyforMap_one();            //地图生成第一关
			//生成整个背景
			loadimage(NULL, _T("Floor.jpg"));          //背景地图
			gamemap.PrintMap_1();
			gamemap.PrintMap_2();			
			messageboard.Print();
			Sleep(1000);
			//画标题，做为入场
			IMAGE img1;
			loadimage(&img1, _T("chapter_1.jpg"));     //读取照片
			putimage(0,300, &img1);
			Sleep(3000);
			mciSendString("open c1.mp3 alias card1Music", NULL, 0, NULL);  	// 打开音乐文件
			mciSendString("play card1Music", NULL, 0, NULL);  //播放音乐
			mciSendString("play card1Music repeat", NULL, 0, NULL);  //播放音乐
		}
		else if (card == 2)
		{
			//地图生成第二关
		}



		BeginBatchDraw();          //开始批量绘图
		//循环游戏过程
		while (1)
		{

			time++;

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

			//生成敌方普通坦克	
			if (gamemap.GetNumNormalTank() > 0 && NormalTank.size() < 3)   //场上少于3个敌方坦克且坦克还有剩余
			{
				NormalAITank *p = new NormalAITank();        //分配tank内存
				gamemap.KillNormalTank();                  //减少剩余敌方坦克数量
				random = rand();     //随机数
				p->Setxy(gamemap.CreatObjectXY(random));         //随机分配位置
				NormalTank.push_back(p);          //压入
			}

			//生成敌方精英坦克
			if (gamemap.GetNumBossTank() > 0 && gamemap.GetNumNormalTank() < 3 && BossTank.size() < 1)  //有剩余，普通坦克剩余3，精英少于1
			{
				BossAITank *p = new BossAITank();        //分配tank内存
				gamemap.KillBossTank();                  //减少剩余敌方坦克数量
				random = rand();     //随机数
				p->Setxy(gamemap.CreatObjectXY(random));         //随机分配位置
				BossTank.push_back(p);          //压入
			}

			//生成buff
			if (AllBuff.empty() && time > 100 &&!player.GetBuff())  //场上没有buff   10s之后    玩家buff没有全满
			{
				int buff_chose=0;   //0 继续随机选择生成的buff  1 hp     2 speed     3 fire
				int times=0;
				do {
					random = rand() % 3;  //随机
					times++;
					switch (random)
					{
					case 0:  if (player.GetHP() < 3) buff_chose = 1; break;
					case 1:  if (player.GetSpeed() != SpeedLevel_3) buff_chose = 2; break;
					case 2:  if (player.GetFireInterval() != IntervalLevel_3) buff_chose = 3; break;
					}
				} while (!buff_chose&&times<5);  //没找到就继续循环(最多循环五次

				time = 0;                 //重置buff生成时间
				Buff *p=NULL;                  //指针

					if (buff_chose == 1)
						p = new HPBuff();
					else if (buff_chose == 2)
						p = new MoveSpeedBuff();
					else//buff_chose=3
						p = new FireIntervalBuff();

					random = rand();     //随机数
					p->Setxy(gamemap.CreatObjectXY(random));         //随机分配位置
					AllBuff.push_back(p);          //压入
			}



			///////////////////////////////////打印环节//////////////////////////////////////
			loadimage(NULL, _T("Floor.jpg"));          //背景地图
			gamemap.PrintMap_2();   //画地图Map类（根据card确定map  坦克下方
			player.Print();  //打印玩家坦克

			//操作一下buff
			for (Bf = AllBuff.begin(); Bf != AllBuff.end();)
			{
				(*Bf)->Print();

				if (JudgmentCollisionPlayer((*Bf)->Getxy(), player.Getxy())) //被玩家获取
				{
					(*Bf)->BuffEffect(player);       //buff效果
					player.JudgmentBuff();         //检查一下坦克buff
					time = 0;
					Bf = AllBuff.erase(Bf);    //释放内存
				}
				else if(time>3000)                        //超时消失
					Bf = AllBuff.erase(Bf);    //释放内存
				else
					Bf++;
			}

			 //对所有普通敌方坦克操作（判断存活，开火，移动，打印
			for (NT = NormalTank.begin(); NT != NormalTank.end();)
			{
				if ((*NT)->GetHP() == 0)        //判断是否死亡
				{
					(*NT)->TankBoom();
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
			
			//对所有精英敌方坦克操作
			for (BT = BossTank.begin(); BT != BossTank.end();)
			{
				if ((*BT)->GetHP() == 0)        //判断是否死亡
				{
					(*BT)->TankBoom();
					BT = BossTank.erase(BT);       //释放敌方坦克内存
				}
				else
				{
					random = rand();  //随机数
					Dir movedir = (*BT)->BossMoveAI(random);    //调用普通坦克移动ai
					Judgmentxy = (*BT)->Getxy();        //记录当前坦克坐标


					//开火判断（好了就打
					if ((*BT)->GetReadyForFire())
					{
						(*BT)->ChangeReadyForFire(0);     //冷却
						Shell *p = new Shell(movedir, Judgmentxy);   //申请新内存
						p->Print();
						EnemyTankShell.push_back(p);                       //压入炮弹容器
					}



					//修改坦克朝向
					(*BT)->ChangeDir(movedir);
					switch (movedir) {
					case UP:
						Judgmentxy.Y -= SpeedLevel_3;
						break;
					case DOWN:
						Judgmentxy.Y += SpeedLevel_3;
						break;
					case LEFT:
						Judgmentxy.X -= SpeedLevel_3;
						break;
					case RIGHT:
						Judgmentxy.X += SpeedLevel_3;
						break;
					}

					if (gamemap.GetTankAdmit(Judgmentxy)                                  //判断四角是否与地形碰撞
						&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
						&& gamemap.GetTankAdmit({ Judgmentxy.X ,Judgmentxy.Y + 59 })
						&& gamemap.GetTankAdmit({ Judgmentxy.X + 59,Judgmentxy.Y })
						&& !gamemap.JudgmentBorder(Judgmentxy)                             //判断两角是否超界
						&& !gamemap.JudgmentBorder({ Judgmentxy.X + 59,Judgmentxy.Y + 59 })
						&& !JudgmentTankCollision(Judgmentxy, (*BT)->Getxy())    //判断是否跟敌方坦克碰撞
						&& !JudgmentCollisionPlayer(Judgmentxy, player.Getxy())  //判断是否跟玩家坦克相撞
						)
						(*BT)->MoveTank(movedir);      //移动敌方精英坦克        

					(*BT)->Print();         //打印坦克


					++BT;           //对下一个坦克操作
				}
			}
			
			gamemap.PrintMap_1();  //画地图Map类（根据card确定map   坦克上方




			//遍历对玩家炮弹操作
			for (PTS = PlayerTankShell.begin(); PTS != PlayerTankShell.end();)
			{

				(*PTS)->Print();       //打印炮弹
				(*PTS)->Fly();         //炮弹移动
				COORD Shellxy = (*PTS)->GetXY();  //记录炮弹坐标
				bool flag = 0;        //是否命中敌方坦克的标志

				for (NT = NormalTank.begin(); NT != NormalTank.end(); NT++)      //遍历普通坦克来确认有没有命中
				{
					if (JudgmentKill(Shellxy, (*NT)->Getxy()))  //命中
					{
						(*NT)->ChangeHp(0);              //减少HP
						flag = 1;
						break;
					}
				}

				for (BT = BossTank.begin(); BT != BossTank.end(); BT++)      //遍历精英坦克来确认有没有命中
				{
					if (JudgmentKill(Shellxy, (*BT)->Getxy()))  //命中
					{
						(*BT)->ChangeHp(0);              //减少HP
						flag = 1;
						break;
					}
				}

				if (!gamemap.GetShellAdmit((*PTS)->GetXY()))			          //判断是否打到地形
				{
					gamemap.ChangeMap((*PTS)->GetXY()); //修改地图（减少墙体耐久
					(*PTS)->PrintShellBoom();          //爆炸特效
					PTS = PlayerTankShell.erase(PTS);	//命中删除并释放内存
				}
				else if (JudgmentShellCollision((*PTS)->GetXY(),(*PTS)->GetDir()))         //炮弹对撞
				{
					(*PTS)->PrintShellBoom();          //爆炸特效
					PTS = PlayerTankShell.erase(PTS);	//删除并释放内存
				}
				else if (gamemap.JudgmentBorder((*PTS)->GetXY()) || flag)          //炮弹超界或击杀
				{
					(*PTS)->PrintShellBoom();          //爆炸特效
					PTS = PlayerTankShell.erase(PTS);	//删除并释放内存
				}
				else             //处理下一棵炮弹
				{
					++PTS;
				}
			}

			//遍历对敌方炮弹操作
			for (ETS = EnemyTankShell.begin(); ETS != EnemyTankShell.end();)
			{

				(*ETS)->Print();       //打印炮弹
				(*ETS)->Fly();         //炮弹移动

				if (!gamemap.GetShellAdmit((*ETS)->GetXY()))			          //判断是否打到地形
				{
					gamemap.ChangeMap((*ETS)->GetXY()); //修改地图（减少墙体耐久
					(*ETS)->PrintShellBoom();          //爆炸特效
					ETS = EnemyTankShell.erase(ETS);	//命中删除并释放内存
				}
				else if (gamemap.JudgmentBorder((*ETS)->GetXY()))          //炮弹超界
				{
					(*ETS)->PrintShellBoom();          //爆炸特效
					ETS = EnemyTankShell.erase(ETS);	//释放内存
				}
				else if (JudgmentKill((*ETS)->GetXY(), player.Getxy()))      //命中玩家
				{
					player.ChangeHp(0);      //失去HP
					(*ETS)->PrintShellBoom();          //爆炸特效
					ETS = EnemyTankShell.erase(ETS);	//删除并释放内存
				}
				else if (JudgmentKill((*ETS)->GetXY(), { 570,720 }))  //命中home
				{
					(*ETS)->PrintShellBoom();          //爆炸特效
					player.HomeKill();  //血量归零
				}
				else             //处理下一棵炮弹
					++ETS;
			}



			player.FireIntevalFigure();          //计算玩家开火冷却缩减
			for (NT = NormalTank.begin(); NT != NormalTank.end(); NT++)
				(*NT)->FireIntevalFigure();      //计算敌方普通坦克炮弹冷却
			for (BT = BossTank.begin(); BT != BossTank.end(); BT++)
				(*BT)->FireIntevalFigure();      //计算敌方精英坦克炮弹冷却


			messageboard.ChangeTankMessage(player); //录入玩家坦克状态
			messageboard.Print();               //打印信息板
			//跳出
			if (player.GetHP() == 0 || BossTank.size() + NormalTank.size()==0)  //玩家生命值归零||敌方坦克全部死亡
				break;


			FlushBatchDraw();  //批量绘图
			Sleep(GameSpeed); //游戏延迟
		}
		EndBatchDraw();         //结束批量绘图
		gamemap.CloseMap();     //释放地图内存
		PlayerTankShell.clear();  //清空所有容器
		EnemyTankShell.clear();
		NormalTank.clear();
		BossTank.clear();


		//根据血量判断
		if (player.GetHP() == 0)
		{
			mciSendString("close all", NULL, 0, NULL);   //关闭所有音乐
			GAME.GameOver();    //重新开始/退出
		}
		else
		{
			GAME.GameWin();
			card++;     //进入下一关
		}
	}



	//////////////////////////////////////////////////////////////////测试范围/////////////////////////////////////////////////////////

	return 0;
}


//buff类   ok
//信息版类 ok
//游戏说明 ok
//游戏胜利界面  ok
//游戏bgm
//多线程实现移动射击
//长按移动卡顿


//爆炸效果实现        ok
//精英坦克实装        ok
//第二张地图

//炮弹碰撞bug        ok
//敌方生成卡位bug

