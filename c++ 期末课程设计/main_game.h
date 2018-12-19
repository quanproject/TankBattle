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