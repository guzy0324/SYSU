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
	SOCKET sock;					// socket descriptor
	int cc;							// recv character count
	char *pts;						// pointer to time string
	time_t now;						// current time
	struct sockaddr_in toAddr;		// an Internet endpoint address
	const char *host = "127.0.0.1"; // client IP to connect
	const char *port = "50501";

	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);					 // 加载winsock library，WSVERS为请求版本,wsadata返回系统实际支持的最高版本。
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); // 创建UDP套接字, 参数：因特网协议簇(family)，数据报套接字，UDP协议号， 返回：要监听套接字的描述符或INVALID_SOCKET
	puts("服务器已启动！\n");

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(port)); //atoi：把ascii转化为int. htons：主机序(host)转化为网络序(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);	  //如果host为域名，需要先用函数gethostbyname把域名转化为IP地址
	(void)time(&now);							  // 取得系统时间
	pts = ctime(&now);							  // 把时间转换为字符
	printf("时间：%s", pts);					  // 显示收到时间
	char str[BUFLEN];
	sprintf(str, "\n时间：%s", pts);
	cc = sendto(sock, str, strlen(str), 0, (SOCKADDR *)&toAddr, sizeof(toAddr));
	putchar('\n');
	if (cc == SOCKET_ERROR)
	{
		printf("发送失败，错误号：%d\n", WSAGetLastError());
	}
	closesocket(sock);
	WSACleanup(); // 卸载某版本的DLL
}
