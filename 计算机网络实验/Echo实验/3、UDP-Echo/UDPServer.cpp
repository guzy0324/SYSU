/* UDPServer.cpp */

#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>

#define BUFLEN 2000				   // 缓冲区大小
#define WSVERS MAKEWORD(2, 2)	   // 指明版本2.2
#pragma comment(lib, "ws2_32.lib") // 加载winsock 2.2 Llibrary

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
	WSAStartup(WSVERS, &wsadata);					 // 加载winsock library，WSVERS为请求版本,wsadata返回系统实际支持的最高版本。
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); // 创建UDP套接字, 参数：因特网协议簇(family)，数据报套接字，UDP协议号， 返回：要监听套接字的描述符或INVALID_SOCKET
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;				  // 绑定(监听)所有的接口。
	sin.sin_port = htons((u_short)atoi(service));	  // 绑定指定接口。atoi--把ascii转化为int，htons -- 主机序(host)转化为网络序(network), 为short类型。
	bind(sock, (struct sockaddr *)&sin, sizeof(sin)); // 绑定本地端口号（和本地IP地址)
	puts("服务器已启动！\n");

	while (!_kbhit())
	{																	   //检测是否有按键
		cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&from, &fromsize); //接收客户数据。返回结果：cc为接收的字符数，from中将包含客户IP地址和端口号。
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
			printf("内容：%s\n", buf); // 显示所接收的字符串
			(void)time(&now);		   // 取得系统时间
			pts = ctime(&now);		   // 把时间转换为字符
			printf("时间：%s", pts);   // 显示收到时间
			printf("客户端IP地址：%d.%d.%d.%d\n", from.sin_addr.S_un.S_un_b.s_b1,
				   from.sin_addr.S_un.S_un_b.s_b2,
				   from.sin_addr.S_un.S_un_b.s_b3,
				   from.sin_addr.S_un.S_un_b.s_b4);		 // 显示客户端IP地址
			printf("客户端端口号：%d\n", from.sin_port); // 显示客户端端口号
			char str[BUFLEN];
			sprintf(str, "内容：%s\n时间：%s客户端IP地址：%d.%d.%d.%d\n客户端端口号：%d\n", buf, pts,
					from.sin_addr.S_un.S_un_b.s_b1,
					from.sin_addr.S_un.S_un_b.s_b2,
					from.sin_addr.S_un.S_un_b.s_b3,
					from.sin_addr.S_un.S_un_b.s_b4,
					from.sin_port);
			cc = sendto(sock, str, strlen(str), 0, (SOCKADDR *)&from, sizeof(from));
			putchar('\n');
			if (cc == SOCKET_ERROR)
			{
				printf("发送失败，错误号：%d\n", WSAGetLastError());
			}
		}
	}
	closesocket(sock);
	WSACleanup(); // 卸载某版本的DLL
}
