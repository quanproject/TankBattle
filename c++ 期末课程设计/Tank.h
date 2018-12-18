#pragma once
class Tank
{
public:
	Tank();
	~Tank();
	void MoveTank();                   //坦克移动
	void ChangSpeed(int newspeed);     //修改坦克速度
	void ChangHp(int flag);
	void Fire(int dir);                //开火
	void Setxy(COORD xy);              //设置坦克初始位置
	void ChangeFireInterval(int Newinterval);         //修改攻击间隔
	//修改攻速
private:
	int Speed;           //坦克的移动速度
	int Hp;              //坦克血量
	int Dir;             //坦克面向的方向
	int FireInterval;    //攻击间隔
	COORD XY;            //记录坦克坐标
};

