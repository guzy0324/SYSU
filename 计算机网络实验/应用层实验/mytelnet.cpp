/* TCPClient.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <process.h>
#include <conio.h>
#include <windows.h>

#define BUFLEN 2000           // ��������С
#define WSVERS MAKEWORD(2, 0) // ָ���汾2.0
#define LEFT 75
#define UP 72
#define RIGHT 77
#define DOWN 80

#pragma comment(lib, "ws2_32.lib") // ʹ��winsock 2.0 Llibrary

struct node {
	char ch;
	node* next;
	node* last;
	node(char c, node* cursor) : ch(c), next(cursor) {
		if (cursor != nullptr) {
			last = cursor->last;
			if (last != nullptr) {
				last->next = this;
			}
			cursor->last = this;
		}
		else {
			last = nullptr;
		}
	}
	~node() {
		if (next != nullptr) {
			next->last = last;
		}
		if (last != nullptr) {
			last->next = next;
		}
	}
} *header = new node(0, nullptr);

SOCKET sock;                    // socket descriptor
int kbh;
HANDLE hout;
node* cursor;

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
			putchar('\r');
			for (node* temp = header; temp->ch != 0; temp = temp->next) {
				putchar(' ');
			}
			printf("%s", buf);
			if (kbh != 0) {
				int delta = 0;
				for (node *temp = header; temp->ch != 0; temp = temp->next) {
					putchar(temp->ch);
					if (temp == cursor) {
						delta = 1;
					}
					if (delta > 0) {
						delta++;
					}
				}
				CONSOLE_SCREEN_BUFFER_INFO binfo;
				GetConsoleScreenBufferInfo(hout, &binfo);
				binfo.dwCursorPosition.X -= delta;
				SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
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
int main(int argc, const char *argv[])
{
	if (argc != 3)
	{
		puts("Illegal format!");
		return -1;
	}
	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata); //����winsock library��WSVERSΪ����İ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
	struct hostent* host_temp = gethostbyname(argv[1]);
	system("cls");
	if (host_temp == nullptr)
	{
		printf("Get IP error!");
		return -1;
	}
	const char *host = inet_ntoa(*(struct in_addr*)host_temp->h_addr_list[0]); // server IP to connect
	const char *service = argv[2];  // server port to connect
	struct sockaddr_in sin;         // an Internet endpoint address
	int cc;                         // recv character count
	unsigned threadID;
	
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //�����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
                                                       //���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));                                  // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
	sin.sin_family = AF_INET;                                      // ��������ַ��
	sin.sin_addr.s_addr = inet_addr(host);                         // ���÷�����IP��ַ(32λ)
	sin.sin_port = htons((u_short)atoi(service));                  // ���÷������˿ں�
	int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // ���ӵ����������ڶ�������ָ���ŷ�������ַ�Ľṹ������������Ϊ�ýṹ�Ĵ�С������ֵΪ0ʱ��ʾ�޴�����������SOCKET_ERROR��ʾ����Ӧ�ó����ͨ��WSAGetLastError()��ȡ��Ӧ������롣
	
	InitializeCriticalSection(&cs);   // �ٽ�����ʼ��
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &show, NULL, 0, &threadID);

	char ch;
	while ((ch = getch()) != '\x1b') {
		kbh = -1;
		cursor = header;
		if (ch != '\r')
		{
			do {
				if (ch == 0 || ch == -32) {
					if ((ch = getch()) == LEFT) {
						if (cursor->last != nullptr) {
							cursor = cursor->last;
							putch('\b');
						}
						else {
							putch('\a');
						}
					}
					else if (ch == RIGHT) {
						if (cursor->next != nullptr) {
							cursor = cursor->next;
							CONSOLE_SCREEN_BUFFER_INFO binfo;
							GetConsoleScreenBufferInfo(hout, &binfo);
							binfo.dwCursorPosition.X += 1;
							SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
						}
						else {
							putch('\a');
						}
					}
					else if (ch == UP) {
						cursor = header;
						CONSOLE_SCREEN_BUFFER_INFO binfo;
						GetConsoleScreenBufferInfo(hout, &binfo);
						binfo.dwCursorPosition.X = 0;
						SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
					}
					else if (ch == DOWN) {
						CONSOLE_SCREEN_BUFFER_INFO binfo;
						GetConsoleScreenBufferInfo(hout, &binfo);
						for (; cursor->ch != 0; cursor = cursor->next) {
							binfo.dwCursorPosition.X++;
						}
						SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
					}
				}
				else if (ch == '\b') {
					if (cursor->last != nullptr) {
						if (header == cursor->last) {
							header = cursor;
						}
						delete cursor->last;
						putch('\b');
						CONSOLE_SCREEN_BUFFER_INFO binfo;
						GetConsoleScreenBufferInfo(hout, &binfo);
						for (node* temp = cursor; temp->ch != 0; temp = temp->next) {
							putch(temp->ch);
						}
						putch(' ');
						SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
					}
				}
				else {
					node* temp = new node(ch, cursor);
					CONSOLE_SCREEN_BUFFER_INFO binfo;
					GetConsoleScreenBufferInfo(hout, &binfo);
					if (header == cursor) {
						header = temp;
					}
					for (; temp->ch != 0; temp = temp->next) {
						putch(temp->ch);
					}
					binfo.dwCursorPosition.X++;
					SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
				}
			} while ((ch = getch()) != '\r');
		}
		kbh = 0;
		char buf[BUFLEN + 1];
		int len;
		for (len = 0; len <= BUFLEN && header->ch != 0; ) {
			buf[len++] = header->ch;
			header = header->next;
			delete header->last;
		}
		buf[len++] = '\r';
		buf[len++] = '\n';
		cc = send(sock, buf, len, 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
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
	CloseHandle(hThread);
	shutdown(sock, SD_BOTH);
	closesocket(sock); // �رռ����׽���
	WSACleanup();      // ж��winsock library
}

