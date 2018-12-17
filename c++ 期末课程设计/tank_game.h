#pragma once

#include<iostream>
#include<stdlib.h>
#include<graphics.h>     //easyX图形库
#include<conio.h>
#include<time.h>
#include<windows.h>

//常量定义
const int SIZE = 30;       //绘图使用的标准格数（一格为30像素
const int TANK = 1;        //坦克
const int HOME = 2;        //家
const int SODWALL = 5;     //土墙 易破坏的墙
const int STEEWALL = 6;    //铁墙 不易破坏的墙
const int BRUSH = 7;       //灌木 坦克可以穿越 炮弹无法穿过
const int RIVER = 8;       //河流 坦克不能穿越 炮弹可以穿越
