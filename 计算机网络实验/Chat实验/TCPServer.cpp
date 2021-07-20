/* TCPServer.cpp - main */

#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include <process.h>

#define WSVERS MAKEWORD(2, 0) // 指明版本2.0
#define BUFLEN 2000			  // 缓冲区大小

#pragma comment(lib, "ws2_32.lib") //使用winsock 2.2 library

CRITICAL_SECTION cs;		           // 临界区。每个时刻只有一个线程可以进入临界区
struct node {
	struct sockaddr_in fsin;	   // the from address of a client
	SOCKET ssock;
	HANDLE hThread;
	unsigned threadID;
	node *last;
	node *next;
	node(node *lst, node *nxt): last(lst), next(nxt) {
		if (lst != nullptr) {
			lst->next = this;
		}
		if (nxt != nullptr) {
			nxt->last = this;
		}
	}
	~node() {
		if (last != nullptr) {
			last->next = next;
		}
		if (next != nullptr) {
			next->last = last;
		} 
	}
} *header = nullptr;

unsigned __stdcall trans(void * p)    // 用结构变量或全局变量带入参数
{
	node *ptr = (node *)p;
	struct sockaddr_in fsin = ptr->fsin;	   // the from address of a client
	SOCKET ssock = ptr->ssock;		// slave sockets
	char *pts;						// pointer to time string
	time_t now;						// current time
	char buf[BUFLEN + 1];			// buffer for one line of text

	sprintf(buf, "%d.%d.%d.%d:%d加入群聊！\n",
		fsin.sin_addr.S_un.S_un_b.s_b1,
		fsin.sin_addr.S_un.S_un_b.s_b2,
		fsin.sin_addr.S_un.S_un_b.s_b3,
		fsin.sin_addr.S_un.S_un_b.s_b4,
		fsin.sin_port);
	puts(buf);
	int len = strlen(buf);
	int cc = send(ssock, buf, len, 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
	EnterCriticalSection(&cs);     // 等待进入	
	for (node* temp = ptr->last; temp != nullptr; temp = temp->last) {
		send(temp->ssock, buf, len, 0);
	}
	for (node* temp = ptr->next; temp != nullptr; temp = temp->next) {
		send(temp->ssock, buf, len, 0);
	}
	LeaveCriticalSection(&cs);
	int flag = 1;
	if (cc == SOCKET_ERROR)
	{
		printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
		flag = 0;
	}
	else if (cc == 0)
	{
		puts("Client closed!");
		flag = 0;
	}
	while (flag) {
		cc = recv(ssock, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
		if (cc == SOCKET_ERROR)
		{
			// printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
			sprintf(buf, "%d.%d.%d.%d:%d退出群聊！\n",
				fsin.sin_addr.S_un.S_un_b.s_b1,
				fsin.sin_addr.S_un.S_un_b.s_b2,
				fsin.sin_addr.S_un.S_un_b.s_b3,
				fsin.sin_addr.S_un.S_un_b.s_b4,
				fsin.sin_port);
			puts(buf);
			len = strlen(buf);
			EnterCriticalSection(&cs);     // 等待进入临界区
			for (node* temp = ptr->last; temp != nullptr; temp = temp->last) {
				send(temp->ssock, buf, len, 0);
			}
			for (node* temp = ptr->next; temp != nullptr; temp = temp->next) {
				send(temp->ssock, buf, len, 0);
			}
			LeaveCriticalSection(&cs);
			break;
		}
		else if (cc == 0)
		{
			puts("Client closed!"); // 对方正常关闭
			break;
		}
		else if (cc > 0)
		{
			buf[cc] = '\0';			   // ensure null-termination
			(void)time(&now);		   // 取得系统时间
			pts = ctime(&now);		   // 把时间转换为字符
			char str[BUFLEN];
			sprintf(str, "内容：%s\n时间：%s客户端IP地址：%d.%d.%d.%d\n客户端端口号：%d\n", buf, pts,
				fsin.sin_addr.S_un.S_un_b.s_b1,
				fsin.sin_addr.S_un.S_un_b.s_b2,
				fsin.sin_addr.S_un.S_un_b.s_b3,
				fsin.sin_addr.S_un.S_un_b.s_b4,
				fsin.sin_port);
			puts(str);
			len = strlen(str);
			cc = send(ssock, str, len, 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
			EnterCriticalSection(&cs);     // 等待进入临界区
			for (node* temp = ptr->last; temp != nullptr; temp = temp->last) {
				send(temp->ssock, str, len, 0);
			}
			for (node* temp = ptr->next; temp != nullptr; temp = temp->next) {
				send(temp->ssock, str, len, 0);
			}
			LeaveCriticalSection(&cs);
			if (cc == SOCKET_ERROR)
			{
				printf("\nError: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
				break;
			}
			else if (cc == 0)
			{
				puts("\nClient closed!"); // 对方正常关闭
				break;
			}
		}
	}
	(void)closesocket(ssock); // 关闭连接套接字
	putchar('\n');
	EnterCriticalSection(&cs);     // 等待进入临界区
	if (ptr == header) {
		header = ptr->next;
	}
	delete ptr;
	LeaveCriticalSection(&cs);     // 离开临界区
	
	return 0;                         //返回时自动结束线程。_endthreadex(0)也可以用于结束线程
}

/*------------------------------------------------------------------------
 * main - Iterative TCP server for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
/* argc: 命令行参数个数， 例如：C:\> TCPServer 8080 
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
	SOCKET msock;		   // master & slave sockets
	WSADATA wsadata;			   //使用的动态链接库版本
	const char *service = "50500"; // thelocalport to bind
	struct sockaddr_in sin;		   // an Internet endpoint address
	int alen;					   // from-address length

	WSAStartup(WSVERS, &wsadata);					   // 加载winsock library。WSVERS指明请求使用的版本。wsadata返回系统实际支持的最高版本
	msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // 创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
													   // 返回：要监听套接字的描述符或INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));					   // 从&sin开始的长度为sizeof(sin)的内存清0
	sin.sin_family = AF_INET;						   // 因特网地址簇(INET-Internet)
	sin.sin_addr.s_addr = INADDR_ANY;				   // 监听所有(接口的)IP地址。
	sin.sin_port = htons((u_short)atoi(service));	   // 监听的端口号。atoi--把ascii转化为int，htons--主机序到网络序(host to network，s-short 16位)
	bind(msock, (struct sockaddr *)&sin, sizeof(sin)); // 绑定监听的IP地址和端口号

	listen(msock, 5); // 建立长度为5的连接请求队列，并把到来的连接请求加入队列等待处理。
	InitializeCriticalSection(&cs);   // 临界区初始化
	puts("服务器已启动！\n");

	while (!_kbhit())
	{															// 检测是否有按键,如果没有则进入循环体执行
		alen = sizeof(struct sockaddr);							// 取到地址结构的长度
		header = new node(nullptr, header);
		//header->ssock = 4294967295;
		//while (header->ssock == 4294967295) {
			header->ssock = accept(msock, (struct sockaddr*) & header->fsin, &alen); // 如果在连接请求队列中有连接请求，则接受连接请求并建立连接，返回该连接的套接字，否则，本语句被阻塞直到队列非空。fsin包含客户端IP地址和端口号
		//}

		header->hThread = (HANDLE)_beginthreadex(NULL, 0, &trans, (void *)header, 0, &header->threadID);
	}
	(void)closesocket(msock); // 关闭监听套接字
	WSACleanup();			  // 卸载winsock library
}
