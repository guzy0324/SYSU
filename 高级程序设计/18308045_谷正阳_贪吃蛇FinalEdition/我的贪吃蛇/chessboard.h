#pragma once
#include<iostream>     //c++输入输出流
#include<windows.h>    //windows头文件
#include<time.h>       //c++日期时间头文件
#include<conio.h>      //控制台输入输出头文件
#define H 22           //宏定义
#define W 22           //宏定义
using namespace std;   //引用c++命名空间“std”
class chessboard       // 定义了棋盘类
{
public:
	char qp[H][W];	   //定义数组表示棋盘，核心思想时不同的数组内容表示不同的含义
	int i, j, x1, y1;  //定义棋盘用到的变量
	int grade, length;
	char mode;//模式1或2
	chessboard();      //定义类“chessboard”的构造函数，用于初始化棋盘
	void food();       //定义类“chessboard”的成员函数“food”，用于随机生成食物
	void prt(int grade, int score, int gamespeed); // //更新屏幕显示：棋盘显示等级 分数和游戏速度
};
