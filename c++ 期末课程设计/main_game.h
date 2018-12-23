#pragma once

#include<iostream>
#include<stdlib.h>
#include<graphics.h>     //easyX图形库
#include<conio.h>
#include<time.h>
#include<windows.h>

//常量定义
constexpr auto GAMESIZE = 30;       //绘图使用的标准格数（一格为30像素
const int TANK = 1;        //坦克
const int HOME = 2;        //家
const int SHELL = 3;       //炮弹
const int SODWALL = 5;     //土墙 易破坏的墙
const int STEEWALL = 6;    //铁墙 不易破坏的墙
const int BRUSH = 7;       //灌木 坦克可以穿越 炮弹无法穿过
const int RIVER = 8;       //河流 坦克不能穿越 炮弹可以穿越


//操作常量
constexpr auto UP = 119;       //w 上
constexpr auto DOWN = 115;     //s 下
constexpr auto LEFT = 97;      //a 左
constexpr auto RIGHT = 100;    //d 右
constexpr auto DETER = 106;    //j 开炮/确认
constexpr auto ACT = 107;    //k 道具/退出/返回

constexpr auto PI = 3.1415926535;         //用于旋转图片


//游戏平衡数据
const int SpeedLevel_1 = 6;   //移动速度
const int SpeedLevel_2 = 10;
const int SpeedLevel_3 = 15;

const int IntervalLevel_1 = 30;  //攻击冷却时间
const int IntervalLevel_2 = 23;
const int IntervalLevel_3 = 15;

const int ShellFlySpeed = 20;   //炮弹飞行速度
const int GameSpeed = 30;       //游戏延迟30ms一帧