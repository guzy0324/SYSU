/* TCPClient.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <process.h>
#include <conio.h>

#define BUFLEN 2000           // 缓冲区大小
#define WSVERS MAKEWORD(2, 0) // 指明版本2.0

#pragma comment(lib, "ws2_32.lib") // 使用winsock 2.0 Llibrary

SOCKET sock;                    // socket descriptor
char sbuf[BUFLEN + 1];           // buffer for one line of text
int top;

CRITICAL_SECTION cs;		           // 临界区。每个时刻只有一个线程可以进入临界区
// 刷新和打印屏幕
unsigned __stdcall show(void * p)    // 用结构变量或全局变量带入参数
{
	while (1) {
		char buf[BUFLEN + 1];           // buffer for one line of text
		int cc;                         // recv character count
		cc = recv(sock, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
		if (cc == SOCKET_ERROR)
		{
			printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
			return 0;
		}
		else if (cc > 0)
		{
			buf[cc] = '\0';    // ensure null-termination
			EnterCriticalSection(&cs);     // 等待进入临界区
			if (top > 0) {
				putchar('\r');
			}
			printf("收到的消息：\n%s\n", buf); // 显示所接收的字符串
			if (top > 0) {
				printf("输入要发送的消息：%s", sbuf);
			}
			LeaveCriticalSection(&cs);     // 离开临界区
		}
	}
	return 0;                         //返回时自动结束线程。_endthreadex(0)也可以用于结束线程
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
	WSAStartup(WSVERS, &wsadata); //加载winsock library。WSVERS为请求的版本，wsadata返回系统实际支持的最高版本

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
                                                       //返回：要监听套接字的描述符或INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));                                  // 从&sin开始的长度为sizeof(sin)的内存清0
	sin.sin_family = AF_INET;                                      // 因特网地址簇
	sin.sin_addr.s_addr = inet_addr(host);                         // 设置服务器IP地址(32位)
	sin.sin_port = htons((u_short)atoi(service));                  // 设置服务器端口号
	int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // 连接到服务器，第二个参数指向存放服务器地址的结构，第三个参数为该结构的大小，返回值为0时表示无错误发生，返回SOCKET_ERROR表示出错，应用程序可通过WSAGetLastError()获取相应错误代码。
	
	InitializeCriticalSection(&cs);   // 临界区初始化
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &show, NULL, 0, &threadID);
	
	top = 0;
	char ch;
	while ((ch = getch()) != 'q') {
		if (ch == 'i') {
			printf("%s", "输入要发送的消息：");
			while ((ch = getchar()) != '\n') {
				sbuf[top++] = ch;
			}
			cc = send(sock, sbuf, top, 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
			top = 0;
			putchar('\n');
			if (cc == SOCKET_ERROR)
			{
				printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
				break;
			}
			else if (cc == 0)
			{
				printf("Server closed!"); // 对方正常关闭
				break;
			}
		}
	}
	CloseHandle(hThread);
	closesocket(sock); // 关闭监听套接字
	WSACleanup();      // 卸载winsock library
}
