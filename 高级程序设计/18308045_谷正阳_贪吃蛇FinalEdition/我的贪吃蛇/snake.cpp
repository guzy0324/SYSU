#include "snake.h"
snake::snake()
{
	score = 0;
	head = 3, tail = 0;
	grade = 1, length = 4;
	gamespeed = 500; // 500时间片0.5秒走一步
	direction = 77; // 起始方向-》
	oldDirection = direction;
	breakFlag = 0; //按键异常标志
	for (i = tail; i <= head; i++) //初始化贪吃蛇的坐标
	{
		zb[0][i] = 1;
		zb[1][i] = i + 1;
		if(i!=head)qp[zb[0][i]][zb[1][i]] = '*';//贪吃蛇身体
		else qp[zb[0][i]][zb[1][i]] = '@';//贪吃蛇头
	}
}
void snake::chooseMode() {
	while (1) {
		cout << "\n\n\t\tmode 1(press 1 to start)" << endl << "\n\n\t\tmode 2(press 2 to start)" << endl<<"\n\n\t\t";
		mode = getchar();
		system("cls");
		if (mode == '1' || mode == '2') {
			cout << "\n\n\t\tThe game is about to begin!" << endl;
			for (i = 3; i >= 0; i--) // 321倒计时
			{
				start = clock();     //成员变量开始计时
				while (clock() - start <= 1000); // 暂停1000个系统时间片，1秒
				system("cls");
				if (i > 0)
					cout << "\n\n\t\tCountdown:" << i << endl;
			}
			game();
			break;
		}
	}
}
void snake::game() {
	if (mode == '2') {
		for (i = 1; i <= H - 2; i++)
		{
			for (j = 1; j <= W - 2; j++)
			{
				qp[i][j] = ' ';//棋盘中间置零
			}
		}
		for (i = 0; i <= H - 1; i++)
		{
			qp[0][i] = qp[H - 1][i] = '+';//棋盘中间置+
		}
		for (i = 1; i <= H - 2; i++)
		{
			qp[i][0] = qp[i][W - 1] = '+';//棋盘中间置+
		}
		for (i = 0; i <= head; i++) //棋盘上放置贪吃蛇
		{
			if (i != head)qp[zb[0][i]][zb[1][i]] = '*';//贪吃蛇身体
			else qp[zb[0][i]][zb[1][i]] = '@';//贪吃蛇头
		}
		food(); //每次构造函数调用成员函数food生成食物
	}
	while (1)
	{
		if (mode == '2'&&grade == 5) { system("cls"); cout << "\n\n\t\tYou win!" << endl << "\n\n\t\tTime spent:\t\t" << clock() / 1000.0 << 's' << endl; system("pause");  break; }
		getDirection();
		if (qp[x][y] != ' ' && !(x == x1 && y == y1) && qp[x][y] != '+') { cout << "\tGame over!" << endl; system("pause");  break; }
		move();
	}
}
void snake::putSnake() {
	for (i = head;; i--) //棋盘上放置贪吃蛇
	{
		if (i == -1) { i += 100; }
		if (i == tail) {
			if (qp[zb[0][i]][zb[1][i]] == '#') {
				if (i + 1 == 100) { tail = i - 99; }
				else {tail =  i + 1; }
			}
			else {
				qp[zb[0][i]][zb[1][i]] = '*';
			}
			break;
		}
		else {
			if (qp[zb[0][i]][zb[1][i]] == '#') {
				if (i + 1 == 100) { tail = i - 99; }
				else { tail = i + 1; }
				break;
			}
			else {
				if (i != head)qp[zb[0][i]][zb[1][i]] = '*';//贪吃蛇身体
				else qp[zb[0][i]][zb[1][i]] = '@';//贪吃蛇头
			}
		}
	}
}
void snake::getDirection() {
	timeover = 1;
	start = clock(); //计时开始
	while ((timeover = (clock() - start <= gamespeed)) && !_kbhit()); //等待gamespeed时间自动前进或者有按键输入前进
	//当等待时间超过gamespeed，(timeover = (clock() - start <= gamespeed)为假退出while循环，程序往下运行，此时timeover=0,表示自动前进
	//当有按键输入，_kbhit()位真，！_kbhit()为假，程序往下运行，此时timeover=1,表示按键按下手动前进
	if (timeover)
	{
		_getch();//输入为“上下左右”时，需要获取两次才能得到正确的ASC码 
		direction = _getch();//后去输入方向
		//此写法当输入其他按键时程序会等待下个按键，为暂停效果
	}
	switch (direction) //根据方向贪吃蛇的坐标更新 
	{
		//与当前前进方向相反按键认为按键异常
	case 72:if (oldDirection == 80) { breakFlag = 1; break; }x = zb[0][head] - 1; y = zb[1][head]; oldDirection = direction; break;//坐标更新
	case 80: if (oldDirection == 72) { breakFlag = 1; break; }x = zb[0][head] + 1; y = zb[1][head]; oldDirection = direction; break;//坐标更新
	case 75: if (oldDirection == 77) { breakFlag = 1; break; }x = zb[0][head]; y = zb[1][head] - 1; oldDirection = direction; break;//坐标更新
	case 77: if (oldDirection == 75) { breakFlag = 1; break; }x = zb[0][head]; y = zb[1][head] + 1; oldDirection = direction; break;//坐标更新
	default: breakFlag = 1;//超出上下左右范围的按键认为按键异常
	}
	if (breakFlag) //按键异常处理
	{
		switch (oldDirection) {//保持原有方向继续前进
		case 72: x = zb[0][head] - 1; y = zb[1][head]; direction = oldDirection; break;//坐标更新
		case 80: x = zb[0][head] + 1; y = zb[1][head]; direction = oldDirection; break;//坐标更新
		case 75: x = zb[0][head]; y = zb[1][head] - 1; direction = oldDirection; break;//坐标更新
		case 77: x = zb[0][head]; y = zb[1][head] + 1; direction = oldDirection; break;//坐标更新
		}
		breakFlag = 0; //恢复标志位
	}
	if (qp[x][y] == '+') {
		switch (direction) {//保持原有方向继续前进
		case 72: x = 20; break;//坐标更新
		case 80: x = 1; break;//坐标更新
		case 75: y = 20; break;//坐标更新
		case 77: y = 1; direction = oldDirection; break;//坐标更新
		}
	}
}
void snake::move()
{
	if (x == x1 && y == y1) // 吃到彩蛋
	{
		length++;
		score = score + 100;
		qp[x][y] = '@';
		qp[zb[0][head]][zb[1][head]] = '*';
		head = (head + 1) % 100;
		zb[0][head] = x;
		zb[1][head] = y;
		if (length >= 8)
		{
			gradeUp();
		}
		food();//重新生成食物
		prt(grade, score, gamespeed); //更新屏幕显示
	}
	else
	{
		qp[zb[0][head]][zb[1][head]] = '*';
		head = (head + 1) % 100;
		qp[zb[0][tail]][zb[1][tail]] = ' ';
		tail = (tail + 1) % 100;
		zb[0][head] = x;
		zb[1][head] = y;
		qp[zb[0][head]][zb[1][head]] = '@';
		prt(grade, score, gamespeed);//更新屏幕显示
	}
}
void snake::gradeUp() {
	if (mode == '1') {
		length -= 8;
		grade++;
		if (gamespeed >= 200)
			gamespeed = 550 - grade * 50; //游戏难度等级设置，加速
	}
	else {
		length -= 8;
		grade++;
		if (gamespeed >= 200)
			gamespeed = 550 - grade * 50; //游戏难度等级设置，加速
		if (grade == 2) {
			for (i = 1; i <= H - 2; i++)
			{
				for (j = 1; j <= W - 2; j++)
				{
					if ((i == 10 || i == 11) && j >= 6 && j <= 15) qp[i][j] = '#';
					else qp[i][j] = ' ';//棋盘中间置零
				}
			}
			for (i = 0; i <= H - 1; i++)
			{
				qp[0][i] = qp[H - 1][i] = '+';//棋盘中间置+
			}
			for (i = 1; i <= H - 2; i++)
			{
				qp[i][0] = qp[i][W - 1] = '+';//棋盘中间置+
			}
			putSnake();
		}
		if (grade == 3) {
			for (i = 1; i <= H - 2; i++)
			{
				for (j = 1; j <= W - 2; j++)
				{
					if ((i == 1 || i == 20) && ((j >= 1 && j <= 4) || (j >= 17 && j <= 20))) qp[i][j] = '#';
					else if (((i >= 2 && i <= 4) || (i >= 17 && i <= 19)) && (j == 1 || j == 20)) qp[i][j] = '#';
					else if ((i == 9 || i == 12) && j >= 6 && j <= 15) qp[i][j] = '#';
					else qp[i][j] = ' ';//棋盘中间置零
				}
			}
			for (i = 0; i <= H - 1; i++)
			{
				qp[0][i] = qp[H - 1][i] = '+';//棋盘中间置+
			}
			for (i = 1; i <= H - 2; i++)
			{
				qp[i][0] = qp[i][W - 1] = '+';//棋盘中间置+
			}
			putSnake();
		}
		if (grade == 4) {
			for (i = 1; i <= H - 2; i++)
			{
				for (j = 1; j <= W - 2; j++)
				{
					if (i >= 1 && i <= 10 && (j >= 4 && j <= 5)) qp[i][j] = '#';
					else if (i >= 11 && i <= 20 && (j >= 15 && j <= 16)) qp[i][j] = '#';
					else if (i >= 4 && i <= 5 && (j >= 11 && j <= 20)) qp[i][j] = '#';
					else if (i >= 15 && i <= 16 && (j >= 1 && j <= 10)) qp[i][j] = '#';
					else qp[i][j] = ' ';//棋盘中间置零
				}
			}
			for (i = 0; i <= H - 1; i++)
			{
				qp[0][i] = qp[H - 1][i] = '+';//棋盘中间置+
			}
			for (i = 1; i <= H - 2; i++)
			{
				qp[i][0] = qp[i][W - 1] = '+';//棋盘中间置+
			}
			putSnake();
		}
	}
}