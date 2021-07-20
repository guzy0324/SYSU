/* UDPServer.cpp */

#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>

#define BUFLEN 2000				   // ��������С
#define WSVERS MAKEWORD(2, 2)	   // ָ���汾2.2
#pragma comment(lib, "ws2_32.lib") // ����winsock 2.2 Llibrary

int main(int argc, char *argv[])
{
	const char *service = "50500"; // server port to connect
	struct sockaddr_in sin;		   // an Internet endpoint address
	struct sockaddr_in from;	   // sender address
	int fromsize = sizeof(from);
	char buf[BUFLEN + 1]; // buffer for one line of text
	SOCKET sock;		  // socket descriptor
	int cc;				  // recv character count
	char *pts;			  // pointer to time string
	time_t now;			  // current time

	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);					 // ����winsock library��WSVERSΪ����汾,wsadata����ϵͳʵ��֧�ֵ���߰汾��
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); // ����UDP�׽���, ������������Э���(family)�����ݱ��׽��֣�UDPЭ��ţ� ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;				  // ��(����)���еĽӿڡ�
	sin.sin_port = htons((u_short)atoi(service));	  // ��ָ���ӿڡ�atoi--��asciiת��Ϊint��htons -- ������(host)ת��Ϊ������(network), Ϊshort���͡�
	bind(sock, (struct sockaddr *)&sin, sizeof(sin)); // �󶨱��ض˿ںţ��ͱ���IP��ַ)
	puts("��������������\n");

	while (!_kbhit())
	{																	   //����Ƿ��а���
		cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&from, &fromsize); //���տͻ����ݡ����ؽ����ccΪ���յ��ַ�����from�н������ͻ�IP��ַ�Ͷ˿ںš�
		if (cc == SOCKET_ERROR)
		{
			printf("recvfrom() failed; %d\n", WSAGetLastError());
			break;
		}
		else if (cc == 0)
		{
			break;
		}
		else
		{
			buf[cc] = '\0';			   // ensure null-termination
			printf("���ݣ�%s\n", buf); // ��ʾ�����յ��ַ���
			(void)time(&now);		   // ȡ��ϵͳʱ��
			pts = ctime(&now);		   // ��ʱ��ת��Ϊ�ַ�
			printf("ʱ�䣺%s", pts);   // ��ʾ�յ�ʱ��
			printf("�ͻ���IP��ַ��%d.%d.%d.%d\n", from.sin_addr.S_un.S_un_b.s_b1,
				   from.sin_addr.S_un.S_un_b.s_b2,
				   from.sin_addr.S_un.S_un_b.s_b3,
				   from.sin_addr.S_un.S_un_b.s_b4);		 // ��ʾ�ͻ���IP��ַ
			printf("�ͻ��˶˿ںţ�%d\n", from.sin_port); // ��ʾ�ͻ��˶˿ں�
			char str[BUFLEN];
			sprintf(str, "���ݣ�%s\nʱ�䣺%s�ͻ���IP��ַ��%d.%d.%d.%d\n�ͻ��˶˿ںţ�%d\n", buf, pts,
					from.sin_addr.S_un.S_un_b.s_b1,
					from.sin_addr.S_un.S_un_b.s_b2,
					from.sin_addr.S_un.S_un_b.s_b3,
					from.sin_addr.S_un.S_un_b.s_b4,
					from.sin_port);
			cc = sendto(sock, str, strlen(str), 0, (SOCKADDR *)&from, sizeof(from));
			putchar('\n');
			if (cc == SOCKET_ERROR)
			{
				printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
			}
		}
	}
	closesocket(sock);
	WSACleanup(); // ж��ĳ�汾��DLL
}
