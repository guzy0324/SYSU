#pragma once
#include "chessboard.h"
class snake :public chessboard // ��̳м��ɣ�����һ�º����������������̳кò��ã���
{
public:
	int zb[2][100]; //���ڴ��̰���ߵ�����
	long start; //���ڼ�ʱ
	int head, tail, score, gamespeed, timeover, x, y, breakFlag; //��Ϸ��ʹ�õı���
	char direction;    //̰����ǰ������ASIC��������ʾ��ʽ
	char oldDirection; //����������õ�����ʱ����
	snake(); //���캯��
	void chooseMode();
	void game();
	void putSnake();
	void getDirection();
	void move();//��Ա����������̰�����ƶ�������ÿ500ms����һ��
	void gradeUp();
};