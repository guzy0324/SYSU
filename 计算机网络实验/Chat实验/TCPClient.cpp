/* TCPClient.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <process.h>
#include <conio.h>

#define BUFLEN 2000           // ��������С
#define WSVERS MAKEWORD(2, 0) // ָ���汾2.0

#pragma comment(lib, "ws2_32.lib") // ʹ��winsock 2.0 Llibrary

SOCKET sock;                    // socket descriptor
char sbuf[BUFLEN + 1];           // buffer for one line of text
int top;

CRITICAL_SECTION cs;		           // �ٽ�����ÿ��ʱ��ֻ��һ���߳̿��Խ����ٽ���
// ˢ�ºʹ�ӡ��Ļ
unsigned __stdcall show(void * p)    // �ýṹ������ȫ�ֱ����������
{
	while (1) {
		char buf[BUFLEN + 1];           // buffer for one line of text
		int cc;                         // recv character count
		cc = recv(sock, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
		if (cc == SOCKET_ERROR)
		{
			printf("Error: %d.\n", GetLastError()); // ����������ر��׽���sock
			return 0;
		}
		else if (cc > 0)
		{
			buf[cc] = '\0';    // ensure null-termination
			EnterCriticalSection(&cs);     // �ȴ������ٽ���
			if (top > 0) {
				putchar('\r');
			}
			printf("�յ�����Ϣ��\n%s\n", buf); // ��ʾ�����յ��ַ���
			if (top > 0) {
				printf("����Ҫ���͵���Ϣ��%s", sbuf);
			}
			LeaveCriticalSection(&cs);     // �뿪�ٽ���
		}
	}
	return 0;                         //����ʱ�Զ������̡߳�_endthreadex(0)Ҳ�������ڽ����߳�
}

/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	const char *host = "127.0.0.1"; // server IP to connect
	const char *service = "50500";  // server port to connect
	struct sockaddr_in sin;         // an Internet endpoint address
	int cc;                         // recv character count
	unsigned threadID;
	
	
	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata); //����winsock library��WSVERSΪ����İ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //�����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
                                                       //���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));                                  // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
	sin.sin_family = AF_INET;                                      // ��������ַ��
	sin.sin_addr.s_addr = inet_addr(host);                         // ���÷�����IP��ַ(32λ)
	sin.sin_port = htons((u_short)atoi(service));                  // ���÷������˿ں�
	int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // ���ӵ����������ڶ�������ָ���ŷ�������ַ�Ľṹ������������Ϊ�ýṹ�Ĵ�С������ֵΪ0ʱ��ʾ�޴�����������SOCKET_ERROR��ʾ����Ӧ�ó����ͨ��WSAGetLastError()��ȡ��Ӧ������롣
	
	InitializeCriticalSection(&cs);   // �ٽ�����ʼ��
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &show, NULL, 0, &threadID);
	
	top = 0;
	char ch;
	while ((ch = getch()) != 'q') {
		if (ch == 'i') {
			printf("%s", "����Ҫ���͵���Ϣ��");
			while ((ch = getchar()) != '\n') {
				sbuf[top++] = ch;
			}
			cc = send(sock, sbuf, top, 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
			top = 0;
			putchar('\n');
			if (cc == SOCKET_ERROR)
			{
				printf("Error: %d.\n", GetLastError()); // ����������ر��׽���sock
				break;
			}
			else if (cc == 0)
			{
				printf("Server closed!"); // �Է������ر�
				break;
			}
		}
	}
	CloseHandle(hThread);
	closesocket(sock); // �رռ����׽���
	WSACleanup();      // ж��winsock library
}
