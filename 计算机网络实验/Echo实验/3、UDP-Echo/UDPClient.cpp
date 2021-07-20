/* UDPClient.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUFLEN 2000				   // 缓冲区大小
#define WSVERS MAKEWORD(2, 2)	   // 指明版本2.2
#pragma comment(lib, "ws2_32.lib") // 加载winsock 2.2 Llibrary

int main(int argc, char *argv[])
{
	const char *host = "127.0.0.1"; // server IP to connect
	const char *service = "50500";	// server port to connect
	struct sockaddr_in toAddr;		// an Internet endpoint address
	char buf[BUFLEN + 1];			// buffer for one line of text
	SOCKET sock;					// socket descriptor
	int cc;							// recv character count

	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata); // 启动某版本Socket的DLL

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(service)); //atoi：把ascii转化为int. htons：主机序(host)转化为网络序(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);		 //如果host为域名，需要先用函数gethostbyname把域名转化为IP地址

	printf("%s", "输入要发送的消息：");
	scanf("%s", buf);

	cc = sendto(sock, buf, strlen(buf), 0, (SOCKADDR *)&toAddr, sizeof(toAddr));
	putchar('\n');
	if (cc == SOCKET_ERROR)
	{
		printf("发送失败，错误号：%d\n", WSAGetLastError());
	}
	else
	{
		int temp = sizeof(toAddr);
		cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&toAddr, &temp); //接收服务器数据。返回结果：cc为接收的字符数，toAddr中将包含服务器IP地址和端口号。
		if (cc == SOCKET_ERROR)
		{
			printf("recvfrom() failed; %d\n", WSAGetLastError());
		}
		else if (cc > 0)
		{
			buf[cc] = '\0';					   // ensure null-termination
			printf("收到的消息：\n%s\n", buf); // 显示所接收的字符串
		}
	}

	closesocket(sock);
	WSACleanup(); // 卸载某版本的DLL
}
