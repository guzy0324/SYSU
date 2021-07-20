#pragma once
#include "chessboard.h"
class snake :public chessboard // 类继承技巧，考虑一下和五子棋的区别，这个继承好不好？？
{
public:
	int zb[2][100]; //用于存放贪吃蛇的坐标
	long start; //用于计时
	int head, tail, score, gamespeed, timeover, x, y, breakFlag; //游戏内使用的标量
	char direction;    //贪吃蛇前进方向，ASIC码数字显示方式
	char oldDirection; //方向更新是用到的临时方向
	snake(); //构造函数
	void chooseMode();
	void game();
	void putSnake();
	void getDirection();
	void move();//成员函数，表征贪吃蛇移动动作，每500ms更新一次
	void gradeUp();
};