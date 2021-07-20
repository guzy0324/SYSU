#include "snake.h"
snake::snake()
{
	score = 0;
	head = 3, tail = 0;
	grade = 1, length = 4;
	gamespeed = 500; // 500ʱ��Ƭ0.5����һ��
	direction = 77; // ��ʼ����-��
	oldDirection = direction;
	breakFlag = 0; //�����쳣��־
	for (i = tail; i <= head; i++) //��ʼ��̰���ߵ�����
	{
		zb[0][i] = 1;
		zb[1][i] = i + 1;
		if(i!=head)qp[zb[0][i]][zb[1][i]] = '*';//̰��������
		else qp[zb[0][i]][zb[1][i]] = '@';//̰����ͷ
	}
}
void snake::chooseMode() {
	while (1) {
		cout << "\n\n\t\tmode 1(press 1 to start)" << endl << "\n\n\t\tmode 2(press 2 to start)" << endl<<"\n\n\t\t";
		mode = getchar();
		system("cls");
		if (mode == '1' || mode == '2') {
			cout << "\n\n\t\tThe game is about to begin!" << endl;
			for (i = 3; i >= 0; i--) // 321����ʱ
			{
				start = clock();     //��Ա������ʼ��ʱ
				while (clock() - start <= 1000); // ��ͣ1000��ϵͳʱ��Ƭ��1��
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
				qp[i][j] = ' ';//�����м�����
			}
		}
		for (i = 0; i <= H - 1; i++)
		{
			qp[0][i] = qp[H - 1][i] = '+';//�����м���+
		}
		for (i = 1; i <= H - 2; i++)
		{
			qp[i][0] = qp[i][W - 1] = '+';//�����м���+
		}
		for (i = 0; i <= head; i++) //�����Ϸ���̰����
		{
			if (i != head)qp[zb[0][i]][zb[1][i]] = '*';//̰��������
			else qp[zb[0][i]][zb[1][i]] = '@';//̰����ͷ
		}
		food(); //ÿ�ι��캯�����ó�Ա����food����ʳ��
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
	for (i = head;; i--) //�����Ϸ���̰����
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
				if (i != head)qp[zb[0][i]][zb[1][i]] = '*';//̰��������
				else qp[zb[0][i]][zb[1][i]] = '@';//̰����ͷ
			}
		}
	}
}
void snake::getDirection() {
	timeover = 1;
	start = clock(); //��ʱ��ʼ
	while ((timeover = (clock() - start <= gamespeed)) && !_kbhit()); //�ȴ�gamespeedʱ���Զ�ǰ�������а�������ǰ��
	//���ȴ�ʱ�䳬��gamespeed��(timeover = (clock() - start <= gamespeed)Ϊ���˳�whileѭ���������������У���ʱtimeover=0,��ʾ�Զ�ǰ��
	//���а������룬_kbhit()λ�棬��_kbhit()Ϊ�٣������������У���ʱtimeover=1,��ʾ���������ֶ�ǰ��
	if (timeover)
	{
		_getch();//����Ϊ���������ҡ�ʱ����Ҫ��ȡ���β��ܵõ���ȷ��ASC�� 
		direction = _getch();//��ȥ���뷽��
		//��д����������������ʱ�����ȴ��¸�������Ϊ��ͣЧ��
	}
	switch (direction) //���ݷ���̰���ߵ�������� 
	{
		//�뵱ǰǰ�������෴������Ϊ�����쳣
	case 72:if (oldDirection == 80) { breakFlag = 1; break; }x = zb[0][head] - 1; y = zb[1][head]; oldDirection = direction; break;//�������
	case 80: if (oldDirection == 72) { breakFlag = 1; break; }x = zb[0][head] + 1; y = zb[1][head]; oldDirection = direction; break;//�������
	case 75: if (oldDirection == 77) { breakFlag = 1; break; }x = zb[0][head]; y = zb[1][head] - 1; oldDirection = direction; break;//�������
	case 77: if (oldDirection == 75) { breakFlag = 1; break; }x = zb[0][head]; y = zb[1][head] + 1; oldDirection = direction; break;//�������
	default: breakFlag = 1;//�����������ҷ�Χ�İ�����Ϊ�����쳣
	}
	if (breakFlag) //�����쳣����
	{
		switch (oldDirection) {//����ԭ�з������ǰ��
		case 72: x = zb[0][head] - 1; y = zb[1][head]; direction = oldDirection; break;//�������
		case 80: x = zb[0][head] + 1; y = zb[1][head]; direction = oldDirection; break;//�������
		case 75: x = zb[0][head]; y = zb[1][head] - 1; direction = oldDirection; break;//�������
		case 77: x = zb[0][head]; y = zb[1][head] + 1; direction = oldDirection; break;//�������
		}
		breakFlag = 0; //�ָ���־λ
	}
	if (qp[x][y] == '+') {
		switch (direction) {//����ԭ�з������ǰ��
		case 72: x = 20; break;//�������
		case 80: x = 1; break;//�������
		case 75: y = 20; break;//�������
		case 77: y = 1; direction = oldDirection; break;//�������
		}
	}
}
void snake::move()
{
	if (x == x1 && y == y1) // �Ե��ʵ�
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
		food();//��������ʳ��
		prt(grade, score, gamespeed); //������Ļ��ʾ
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
		prt(grade, score, gamespeed);//������Ļ��ʾ
	}
}
void snake::gradeUp() {
	if (mode == '1') {
		length -= 8;
		grade++;
		if (gamespeed >= 200)
			gamespeed = 550 - grade * 50; //��Ϸ�Ѷȵȼ����ã�����
	}
	else {
		length -= 8;
		grade++;
		if (gamespeed >= 200)
			gamespeed = 550 - grade * 50; //��Ϸ�Ѷȵȼ����ã�����
		if (grade == 2) {
			for (i = 1; i <= H - 2; i++)
			{
				for (j = 1; j <= W - 2; j++)
				{
					if ((i == 10 || i == 11) && j >= 6 && j <= 15) qp[i][j] = '#';
					else qp[i][j] = ' ';//�����м�����
				}
			}
			for (i = 0; i <= H - 1; i++)
			{
				qp[0][i] = qp[H - 1][i] = '+';//�����м���+
			}
			for (i = 1; i <= H - 2; i++)
			{
				qp[i][0] = qp[i][W - 1] = '+';//�����м���+
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
					else qp[i][j] = ' ';//�����м�����
				}
			}
			for (i = 0; i <= H - 1; i++)
			{
				qp[0][i] = qp[H - 1][i] = '+';//�����м���+
			}
			for (i = 1; i <= H - 2; i++)
			{
				qp[i][0] = qp[i][W - 1] = '+';//�����м���+
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
					else qp[i][j] = ' ';//�����м�����
				}
			}
			for (i = 0; i <= H - 1; i++)
			{
				qp[0][i] = qp[H - 1][i] = '+';//�����м���+
			}
			for (i = 1; i <= H - 2; i++)
			{
				qp[i][0] = qp[i][W - 1] = '+';//�����м���+
			}
			putSnake();
		}
	}
}