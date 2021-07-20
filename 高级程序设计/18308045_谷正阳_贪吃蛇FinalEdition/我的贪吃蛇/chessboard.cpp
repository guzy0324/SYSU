#include "snake.h"
chessboard::chessboard()
{
	for (i = 1; i <= H - 2; i++)
	{
		for (j = 1; j <= W - 2; j++)
		{
			qp[i][j] = ' ';//�����м�����
		}
	}
	for (i = 0; i <= H - 1; i++)
	{
		qp[0][i] = qp[H - 1][i] = '#';//�����м���#
	}
	for (i = 1; i <= H - 2; i++)
	{
		qp[i][0] = qp[i][W - 1] = '#';//�����м���#
	}
	food(); //ÿ�ι��캯�����ó�Ա����food����ʳ��
}
void chessboard::food()
{
	srand(time(0));      // ���ʱ��  srand�������������Ҫ����������ӣ�������ͬ���������ͬ;Ϊ��֤���ɵ���������������Ӧѡȡ��ͬ��������ӣ�һ��ѡȡϵͳ��ǰʱ����Ϊ������ӣ���Ϊϵͳʱ���ڱ仯
						  //time(0)��ȥ��ǰϵͳʱ��
	if (mode == '2') {
		if (grade == 1 && length == 7) {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // ���λ��
				y1 = (rand() % (H - 2)) + 1;
			} while ((qp[x1][y1] != ' ') || ((x1 == 10 || x1 == 11) && y1 >= 6 && y1 <= 15));//��֤���ɵ�ʳ���ڿհ״�
		}
		else if (grade == 2 && length == 7) {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // ���λ��
				y1 = (rand() % (H - 2)) + 1;
			} while ((qp[x1][y1] != ' ') || ((x1 == 1 || x1 == 20) && ((y1 >= 1 && y1 <= 4) || (y1 >= 17 && y1 <= 20))) || (((x1 >= 2 && x1 <= 4) || (x1 >= 17 && x1 <= 19)) && (y1 == 1 || y1 == 20)) || ((x1 == 9 || x1 == 12) && y1 >= 6 && y1 <= 15)); //��֤���ɵ�ʳ���ڿհ״�
		}
		else if (grade == 3 && length == 7) {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // ���λ��
				y1 = (rand() % (H - 2)) + 1;
			} while ((qp[x1][y1] != ' ') || (x1 >= 1 && x1 <= 10 && (y1 >= 4 && y1 <= 5)) || (x1 >= 11 && x1 <= 20 && (y1 >= 15 && y1 <= 16)) || (x1 >= 4 && x1 <= 5 && (y1 >= 11 && y1 <= 20)) || (x1 >= 15 && x1 <= 16 && (y1 >= 1 && y1 <= 10))); //��֤���ɵ�ʳ���ڿհ״�
		}
		else {
			do
			{
				x1 = (rand() % (W - 2)) + 1; // ���λ��
				y1 = (rand() % (H - 2)) + 1;
			} while (qp[x1][y1] != ' '); //��֤���ɵ�ʳ���ڿհ״�
		}
	}
	else {
		do
		{
			x1 = rand() % W - 2 + 1; // ���λ��
			y1 = rand() % H - 2 + 1;
		} while (qp[x1][y1] != ' '); //��֤���ɵ�ʳ���ڿհ״�
	}
	qp[x1][y1] = '$'; //����ʳ����״
}
void chessboard::prt(int grade, int score, int gamespeed)
{
	system("cls");//����ϵͳ������cls�����Ļ����cmd��������һ��
	cout << endl; //����
	for (i = 0; i < H; i++) //��ʾ���
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