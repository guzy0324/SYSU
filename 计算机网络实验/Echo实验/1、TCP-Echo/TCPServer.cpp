/* TCPServer.cpp - main */

#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>

#define WSVERS MAKEWORD(2, 0) // ָ���汾2.0
#define BUFLEN 2000			  // ��������С

#pragma comment(lib, "ws2_32.lib") //ʹ��winsock 2.2 library
/*------------------------------------------------------------------------
 * main - Iterative TCP server for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
/* argc: �����в��������� ���磺C:\> TCPServer 8080 
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
	struct sockaddr_in fsin;	   // the from address of a client
	SOCKET msock, ssock;		   // master & slave sockets
	WSADATA wsadata;			   //ʹ�õĶ�̬���ӿ�汾
	const char *service = "50500"; // thelocalport to bind
	struct sockaddr_in sin;		   // an Internet endpoint address
	int alen;					   // from-address length
	char *pts;					   // pointer to time string
	time_t now;					   // current time
	char buf[BUFLEN + 1];		   // buffer for one line of text

	WSAStartup(WSVERS, &wsadata);					   // ����winsock library��WSVERSָ������ʹ�õİ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
	msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // �����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
													   // ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));					   // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
	sin.sin_family = AF_INET;						   // ��������ַ��(INET-Internet)
	sin.sin_addr.s_addr = INADDR_ANY;				   // ��������(�ӿڵ�)IP��ַ��
	sin.sin_port = htons((u_short)atoi(service));	   // �����Ķ˿ںš�atoi--��asciiת��Ϊint��htons--������������(host to network��s-short 16λ)
	bind(msock, (struct sockaddr *)&sin, sizeof(sin)); // �󶨼�����IP��ַ�Ͷ˿ں�

	listen(msock, 5); // ��������Ϊ5������������У����ѵ������������������еȴ�����
	puts("��������������\n");

	while (!_kbhit())
	{															// ����Ƿ��а���,���û�������ѭ����ִ��
		alen = sizeof(struct sockaddr);							// ȡ����ַ�ṹ�ĳ���
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen); // ����������������������������������������󲢽������ӣ����ظ����ӵ��׽��֣����򣬱���䱻����ֱ�����зǿա�fsin�����ͻ���IP��ַ�Ͷ˿ں�

		int cc = recv(ssock, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
		if (cc == SOCKET_ERROR)
		{
			printf("Error: %d.\n", GetLastError()); // ����������ر��׽���sock
		}
		else if (cc == 0)
		{
			puts("Server closed!"); // �Է������ر�
		}
		else if (cc > 0)
		{
			buf[cc] = '\0';					 // ensure null-termination
			printf("�յ�����Ϣ��%s\n", buf); // ��ʾ�����յ��ַ���
			(void)time(&now);				 // ȡ��ϵͳʱ��
			pts = ctime(&now);				 // ��ʱ��ת��Ϊ�ַ�
			printf("�յ�ʱ�䣺%s", pts);	 // ��ʾ�յ�ʱ��
			char str[BUFLEN];
			sprintf(str, "%s%s", pts, buf);
			cc = send(ssock, str, strlen(str), 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
			if (cc == SOCKET_ERROR)
			{
				printf("\nError: %d.\n", GetLastError()); // ����������ر��׽���sock
			}
			else if (cc == 0)
			{
				puts("\nClient closed!"); // �Է������ر�
			}
		}
		(void)closesocket(ssock); // �ر������׽���
		putchar('\n');
	}
	(void)closesocket(msock); // �رռ����׽���
	WSACleanup();			  // ж��winsock library
}
