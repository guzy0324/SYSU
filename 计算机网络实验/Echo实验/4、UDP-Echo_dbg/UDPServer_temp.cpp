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
	SOCKET sock;					// socket descriptor
	int cc;							// recv character count
	char *pts;						// pointer to time string
	time_t now;						// current time
	struct sockaddr_in toAddr;		// an Internet endpoint address
	const char *host = "127.0.0.1"; // client IP to connect
	const char *port = "50501";

	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);					 // ����winsock library��WSVERSΪ����汾,wsadata����ϵͳʵ��֧�ֵ���߰汾��
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); // ����UDP�׽���, ������������Э���(family)�����ݱ��׽��֣�UDPЭ��ţ� ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET
	puts("��������������\n");

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(port)); //atoi����asciiת��Ϊint. htons��������(host)ת��Ϊ������(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);	  //���hostΪ��������Ҫ���ú���gethostbyname������ת��ΪIP��ַ
	(void)time(&now);							  // ȡ��ϵͳʱ��
	pts = ctime(&now);							  // ��ʱ��ת��Ϊ�ַ�
	printf("ʱ�䣺%s", pts);					  // ��ʾ�յ�ʱ��
	char str[BUFLEN];
	sprintf(str, "\nʱ�䣺%s", pts);
	cc = sendto(sock, str, strlen(str), 0, (SOCKADDR *)&toAddr, sizeof(toAddr));
	putchar('\n');
	if (cc == SOCKET_ERROR)
	{
		printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
	}
	closesocket(sock);
	WSACleanup(); // ж��ĳ�汾��DLL
}
