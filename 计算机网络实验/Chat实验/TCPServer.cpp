/* TCPServer.cpp - main */

#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <winsock2.h>
#include <process.h>

#define WSVERS MAKEWORD(2, 0) // ָ���汾2.0
#define BUFLEN 2000			  // ��������С

#pragma comment(lib, "ws2_32.lib") //ʹ��winsock 2.2 library

CRITICAL_SECTION cs;		           // �ٽ�����ÿ��ʱ��ֻ��һ���߳̿��Խ����ٽ���
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

unsigned __stdcall trans(void * p)    // �ýṹ������ȫ�ֱ����������
{
	node *ptr = (node *)p;
	struct sockaddr_in fsin = ptr->fsin;	   // the from address of a client
	SOCKET ssock = ptr->ssock;		// slave sockets
	char *pts;						// pointer to time string
	time_t now;						// current time
	char buf[BUFLEN + 1];			// buffer for one line of text

	sprintf(buf, "%d.%d.%d.%d:%d����Ⱥ�ģ�\n",
		fsin.sin_addr.S_un.S_un_b.s_b1,
		fsin.sin_addr.S_un.S_un_b.s_b2,
		fsin.sin_addr.S_un.S_un_b.s_b3,
		fsin.sin_addr.S_un.S_un_b.s_b4,
		fsin.sin_port);
	puts(buf);
	int len = strlen(buf);
	int cc = send(ssock, buf, len, 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
	EnterCriticalSection(&cs);     // �ȴ�����	
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
		printf("Error: %d.\n", GetLastError()); // ����������ر��׽���sock
		flag = 0;
	}
	else if (cc == 0)
	{
		puts("Client closed!");
		flag = 0;
	}
	while (flag) {
		cc = recv(ssock, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
		if (cc == SOCKET_ERROR)
		{
			// printf("Error: %d.\n", GetLastError()); // ����������ر��׽���sock
			sprintf(buf, "%d.%d.%d.%d:%d�˳�Ⱥ�ģ�\n",
				fsin.sin_addr.S_un.S_un_b.s_b1,
				fsin.sin_addr.S_un.S_un_b.s_b2,
				fsin.sin_addr.S_un.S_un_b.s_b3,
				fsin.sin_addr.S_un.S_un_b.s_b4,
				fsin.sin_port);
			puts(buf);
			len = strlen(buf);
			EnterCriticalSection(&cs);     // �ȴ������ٽ���
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
			puts("Client closed!"); // �Է������ر�
			break;
		}
		else if (cc > 0)
		{
			buf[cc] = '\0';			   // ensure null-termination
			(void)time(&now);		   // ȡ��ϵͳʱ��
			pts = ctime(&now);		   // ��ʱ��ת��Ϊ�ַ�
			char str[BUFLEN];
			sprintf(str, "���ݣ�%s\nʱ�䣺%s�ͻ���IP��ַ��%d.%d.%d.%d\n�ͻ��˶˿ںţ�%d\n", buf, pts,
				fsin.sin_addr.S_un.S_un_b.s_b1,
				fsin.sin_addr.S_un.S_un_b.s_b2,
				fsin.sin_addr.S_un.S_un_b.s_b3,
				fsin.sin_addr.S_un.S_un_b.s_b4,
				fsin.sin_port);
			puts(str);
			len = strlen(str);
			cc = send(ssock, str, len, 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
			EnterCriticalSection(&cs);     // �ȴ������ٽ���
			for (node* temp = ptr->last; temp != nullptr; temp = temp->last) {
				send(temp->ssock, str, len, 0);
			}
			for (node* temp = ptr->next; temp != nullptr; temp = temp->next) {
				send(temp->ssock, str, len, 0);
			}
			LeaveCriticalSection(&cs);
			if (cc == SOCKET_ERROR)
			{
				printf("\nError: %d.\n", GetLastError()); // ����������ر��׽���sock
				break;
			}
			else if (cc == 0)
			{
				puts("\nClient closed!"); // �Է������ر�
				break;
			}
		}
	}
	(void)closesocket(ssock); // �ر������׽���
	putchar('\n');
	EnterCriticalSection(&cs);     // �ȴ������ٽ���
	if (ptr == header) {
		header = ptr->next;
	}
	delete ptr;
	LeaveCriticalSection(&cs);     // �뿪�ٽ���
	
	return 0;                         //����ʱ�Զ������̡߳�_endthreadex(0)Ҳ�������ڽ����߳�
}

/*------------------------------------------------------------------------
 * main - Iterative TCP server for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
/* argc: �����в��������� ���磺C:\> TCPServer 8080 
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
	SOCKET msock;		   // master & slave sockets
	WSADATA wsadata;			   //ʹ�õĶ�̬���ӿ�汾
	const char *service = "50500"; // thelocalport to bind
	struct sockaddr_in sin;		   // an Internet endpoint address
	int alen;					   // from-address length

	WSAStartup(WSVERS, &wsadata);					   // ����winsock library��WSVERSָ������ʹ�õİ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
	msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // �����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
													   // ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));					   // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
	sin.sin_family = AF_INET;						   // ��������ַ��(INET-Internet)
	sin.sin_addr.s_addr = INADDR_ANY;				   // ��������(�ӿڵ�)IP��ַ��
	sin.sin_port = htons((u_short)atoi(service));	   // �����Ķ˿ںš�atoi--��asciiת��Ϊint��htons--������������(host to network��s-short 16λ)
	bind(msock, (struct sockaddr *)&sin, sizeof(sin)); // �󶨼�����IP��ַ�Ͷ˿ں�

	listen(msock, 5); // ��������Ϊ5������������У����ѵ������������������еȴ�����
	InitializeCriticalSection(&cs);   // �ٽ�����ʼ��
	puts("��������������\n");

	while (!_kbhit())
	{															// ����Ƿ��а���,���û�������ѭ����ִ��
		alen = sizeof(struct sockaddr);							// ȡ����ַ�ṹ�ĳ���
		header = new node(nullptr, header);
		//header->ssock = 4294967295;
		//while (header->ssock == 4294967295) {
			header->ssock = accept(msock, (struct sockaddr*) & header->fsin, &alen); // ����������������������������������������󲢽������ӣ����ظ����ӵ��׽��֣����򣬱���䱻����ֱ�����зǿա�fsin�����ͻ���IP��ַ�Ͷ˿ں�
		//}

		header->hThread = (HANDLE)_beginthreadex(NULL, 0, &trans, (void *)header, 0, &header->threadID);
	}
	(void)closesocket(msock); // �رռ����׽���
	WSACleanup();			  // ж��winsock library
}
