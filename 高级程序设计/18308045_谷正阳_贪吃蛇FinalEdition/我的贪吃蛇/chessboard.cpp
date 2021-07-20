#include "snake.h"
chessboard::chessboard()
{
	for (i = 1; i <= H - 2; i++)
	{
		for (j = 1; j <= W - 2; j++)
		{
			qp[i][j] = ' ';//棋盘中间置零
		}
	}
	for (i = 0; i <= H - 1; i++)
	{
		qp[0][i] = qp[H - 1][i] = '#';//棋盘中间置#
	}
	for (i = 1; i <= H - 2; i++)
	{
		qp[i][0] = qp[i][W - 1] = '#';//棋盘中间置#
	}
	food(); //每次构造函数调用成员函数food生成食物
}
void chessboard::food()
{
	srand(time(0));      // 随机时间  srand生成随机数，需要输入随机种子，种子相同则随机数相同;为保证生成的随机数具有随机性应选取不同的随机种子，一般选取系统当前时间最为随机种子，因为系统时间在变化
						  //time(0)回去当前系统时间
	if (mode == '2') {
		if (grade == 1 && length == 7) {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // 随机位置
				y1 = (rand() % (H - 2)) + 1;
			} while ((qp[x1][y1] != ' ') || ((x1 == 10 || x1 == 11) && y1 >= 6 && y1 <= 15));//保证生成的食物在空白处
		}
		else if (grade == 2 && length == 7) {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // 随机位置
				y1 = (rand() % (H - 2)) + 1;
			} while ((qp[x1][y1] != ' ') || ((x1 == 1 || x1 == 20) && ((y1 >= 1 && y1 <= 4) || (y1 >= 17 && y1 <= 20))) || (((x1 >= 2 && x1 <= 4) || (x1 >= 17 && x1 <= 19)) && (y1 == 1 || y1 == 20)) || ((x1 == 9 || x1 == 12) && y1 >= 6 && y1 <= 15)); //保证生成的食物在空白处
		}
		else if (grade == 3 && length == 7) {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // 随机位置
				y1 = (rand() % (H - 2)) + 1;
			} while ((qp[x1][y1] != ' ') || (x1 >= 1 && x1 <= 10 && (y1 >= 4 && y1 <= 5)) || (x1 >= 11 && x1 <= 20 && (y1 >= 15 && y1 <= 16)) || (x1 >= 4 && x1 <= 5 && (y1 >= 11 && y1 <= 20)) || (x1 >= 15 && x1 <= 16 && (y1 >= 1 && y1 <= 10))); //保证生成的食物在空白处
		}
		else {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // 随机位置
				y1 = (rand() % (H - 2)) + 1;
			} while (qp[x1][y1] != ' '); //保证生成的食物在空白处
		}
	}
	else {
		do
		{
			x1 = rand() % W - 2 + 1; // 随机位置
			y1 = rand() % H - 2 + 1;
		} while (qp[x1][y1] != ' '); //保证生成的食物在空白处
	}
	qp[x1][y1] = '$'; //设置食物形状
}
void chessboard::prt(int grade, int score, int gamespeed)
{
	system("cls");//调用系统命令行cls清空屏幕，与cmd中命令行一致
	cout << endl; //换行
	for (i = 0; i < H; i++) //显示结果
	{
		cout << "\t";
		for (j = 0; j < W; j++)
			cout << qp[i][j] << ' ';
		if (i == 0) cout << "\tTime:" << clock() / 1000.0 << 's';
		if (i == 2) cout << "\tGrade:" << grade;
		if (i == 4) cout << "\tScore:" << score;
		if (i == 6) cout << "\tAutomatic forward";
		if (i == 7) cout << "\ttime interval:" << gamespeed << "ms";

		cout << endl;
	}
}