#pragma once
#include<iostream>     //c++���������
#include<windows.h>    //windowsͷ�ļ�
#include<time.h>       //c++����ʱ��ͷ�ļ�
#include<conio.h>      //����̨�������ͷ�ļ�
#define H 22           //�궨��
#define W 22           //�궨��
using namespace std;   //����c++�����ռ䡰std��
class chessboard       // ������������
{
public:
	char qp[H][W];	   //���������ʾ���̣�����˼��ʱ��ͬ���������ݱ�ʾ��ͬ�ĺ���
	int i, j, x1, y1;  //���������õ��ı���
	int grade, length;
	char mode;//ģʽ1��2
	chessboard();      //�����ࡰchessboard���Ĺ��캯�������ڳ�ʼ������
	void food();       //�����ࡰchessboard���ĳ�Ա������food���������������ʳ��
	void prt(int grade, int score, int gamespeed); // //������Ļ��ʾ��������ʾ�ȼ� ��������Ϸ�ٶ�
};
