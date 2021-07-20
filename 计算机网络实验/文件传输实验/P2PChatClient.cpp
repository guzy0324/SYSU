/* TCPClient.cpp */

#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <io.h>
#include <process.h>
#include <regex>
#include <winsock2.h>
#include <windows.h>
using namespace std;

#define BUFLEN 2000			  // 缓冲区大小
#define WSVERS MAKEWORD(2, 0) // 指明版本2.0
#define LEFT 75
#define UP 72
#define RIGHT 77
#define DOWN 80
#define PARANUM 1
#define FNAME_LEN 20

#pragma comment(lib, "ws2_32.lib") // 使用winsock 2.0 Llibrary
struct FileStruct
{
	char fileName[FNAME_LEN];
	__int64 fileSize;
};

struct node
{
	char ch;
	node *next;
	node *last;
	node(char c, node *cursor) : ch(c), next(cursor)
	{
		if (cursor != nullptr)
		{
			last = cursor->last;
			if (last != nullptr)
			{
				last->next = this;
			}
			cursor->last = this;
		}
		else
		{
			last = nullptr;
		}
	}
	~node()
	{
		if (next != nullptr)
		{
			next->last = last;
		}
		if (last != nullptr)
		{
			last->next = next;
		}
	}
} *header = new node(0, nullptr);

SOCKET sock; // socket descriptor
char* msg[] = {"输入要发送的消息：", "输入命令："};
int kbh = -1;
HANDLE hout;
node *cursor;
char destdname[BUFLEN + 1] = { 'C', ':', '/', 0 };

CRITICAL_SECTION cs; // 临界区。每个时刻只有一个线程可以进入临界区
// 刷新和打印屏幕
unsigned __stdcall show(void *p) // 用结构变量或全局变量带入参数
{
	while (1)
	{
		char buf[BUFLEN + 1];			 // buffer for one line of text
		int cc;							 // recv character count
		cc = recv(sock, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
		if (cc == SOCKET_ERROR)
		{
			printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
			return 0;
		}
		else if (cc > 0)
		{
			switch (buf[0])
			{
			case 'm':
				buf[cc] = '\0';						  // ensure null-termination
				EnterCriticalSection(&cs);			  // 等待进入临界区
				printf("%s", "\r收到的消息：      "); // 显示所接收的字符串
				for (node* temp = header; temp->ch != 0; temp = temp->next)
				{
					putchar(' ');
				}
				printf("\n%s\n", buf + 1);
				if (kbh != -1)
				{
					printf("%s", msg[kbh]);
					int delta = 0;
					for (node* temp = header; temp->ch != 0; temp = temp->next)
					{
						putchar(temp->ch);
						if (temp == cursor)
						{
							delta = 1;
						}
						if (delta > 0)
						{
							delta++;
						}
					}
					CONSOLE_SCREEN_BUFFER_INFO binfo;
					GetConsoleScreenBufferInfo(hout, &binfo);
					binfo.dwCursorPosition.X -= delta;
					SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
				}
				LeaveCriticalSection(&cs); // 离开临界区
				break;
			case 'f':
				char* buf_ptr = buf + 1;
				FileStruct fs = *(FileStruct*)buf_ptr;
				buf_ptr += sizeof(FileStruct);
				char destfname[BUFLEN];
				FILE* destfile = NULL;
				regex pattern("\\.[^.]*$", regex::icase);
				sprintf_s(destfname, "%s/%s", destdname, fs.fileName);
				if (fopen_s(&destfile, destfname, "rb") == NULL) {
					fclose(destfile);
					int i = 1;
					string temp(fs.fileName);
					smatch result;
					if (regex_search(temp, result, pattern))
					{
						sprintf_s(fs.fileName, "%s(%d)%s", &((string)result.prefix())[0], i++, &((string)result[0])[0]);
					}
					sprintf_s(destfname, "%s/%s", destdname, fs.fileName);
					while (fopen_s(&destfile, destfname, "rb") == NULL) {
						fclose(destfile);
						sprintf_s(fs.fileName, "%s(%d)%s", &((string)result.prefix())[0], i++, &((string)result[0])[0]);
						sprintf_s(destfname, "%s/%s", destdname, fs.fileName);
					}
				}
				fopen_s(&destfile, &destfname[0], "wb");
				__int64 len = fs.fileSize;
				// fread的参数：缓冲区起始地址，每个数据(char类型)的字节数，最多读出的数据个数，文件句柄
				//      返回值：实际读出的数据个数
				while (len >= BUFLEN - (buf_ptr - buf)) {
					len -= BUFLEN - (buf_ptr - buf);
					//fwrite的参数：数据起始地址，每个数据(char类型)的字节数，写入数据的个数，文件句柄
					//      返回值：实际写入的数据个数
					fwrite(buf_ptr, 1, BUFLEN - (buf_ptr - buf), destfile);
					cc = recv(sock, buf_ptr, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
					if (cc == SOCKET_ERROR)
					{
						printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
						return 0;
					}
					buf_ptr = buf;
				}
				fwrite(buf, 1, len, destfile);   // 写入剩余部分
				fclose(destfile);
				printf("接收文件%s\n", fs.fileName);
			}
		}
	}
	return 0; //返回时自动结束线程。_endthreadex(0)也可以用于结束线程
}

/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	const char *host = "127.0.0.1"; // server IP to connect
	const char *service = "50500";	// server port to connect
	struct sockaddr_in sin;			// an Internet endpoint address
	int cc;							// recv character count
	unsigned threadID;

	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata); //加载winsock library。WSVERS为请求的版本，wsadata返回系统实际支持的最高版本

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
													  //返回：要监听套接字的描述符或INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));								   // 从&sin开始的长度为sizeof(sin)的内存清0
	sin.sin_family = AF_INET;									   // 因特网地址簇
	sin.sin_addr.s_addr = inet_addr(host);						   // 设置服务器IP地址(32位)
	sin.sin_port = htons((u_short)atoi(service));				   // 设置服务器端口号
	int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // 连接到服务器，第二个参数指向存放服务器地址的结构，第三个参数为该结构的大小，返回值为0时表示无错误发生，返回SOCKET_ERROR表示出错，应用程序可通过WSAGetLastError()获取相应错误代码。

	InitializeCriticalSection(&cs); // 临界区初始化
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &show, NULL, 0, &threadID);

	char buf[BUFLEN + 1];
	char ch;
	while (1)
	{
		ch = getch();
		switch (ch)
		{
			case 'i': kbh = 0; break;
			case ':': kbh = 1; break;
		}
		if (kbh != -1)
		{
			printf("%s", msg[kbh]);
			cursor = header;
			while ((ch = getch()) != '\r')
			{
				if (ch == 0 || ch == -32)
				{
					if ((ch = getch()) == LEFT)
					{
						if (cursor->last != nullptr)
						{
							cursor = cursor->last;
							putch('\b');
						}
						else
						{
							putch('\a');
						}
					}
					else if (ch == RIGHT)
					{
						if (cursor->next != nullptr)
						{
							cursor = cursor->next;
							CONSOLE_SCREEN_BUFFER_INFO binfo;
							GetConsoleScreenBufferInfo(hout, &binfo);
							binfo.dwCursorPosition.X += 1;
							SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
						}
						else
						{
							putch('\a');
						}
					}
					else if (ch == UP)
					{
						cursor = header;
						CONSOLE_SCREEN_BUFFER_INFO binfo;
						GetConsoleScreenBufferInfo(hout, &binfo);
						binfo.dwCursorPosition.X = 18;
						SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
					}
					else if (ch == DOWN)
					{
						CONSOLE_SCREEN_BUFFER_INFO binfo;
						GetConsoleScreenBufferInfo(hout, &binfo);
						for (; cursor->ch != 0; cursor = cursor->next)
						{
							binfo.dwCursorPosition.X++;
						}
						SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
					}
				}
				else if (ch == '\b')
				{
					if (cursor->last != nullptr)
					{
						if (header == cursor->last)
						{
							header = cursor;
						}
						delete cursor->last;
						putch('\b');
						CONSOLE_SCREEN_BUFFER_INFO binfo;
						GetConsoleScreenBufferInfo(hout, &binfo);
						for (node* temp = cursor; temp->ch != 0; temp = temp->next)
						{
							putch(temp->ch);
						}
						putch(' ');
						SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
					}
				}
				else
				{
					node* temp = new node(ch, cursor);
					CONSOLE_SCREEN_BUFFER_INFO binfo;
					GetConsoleScreenBufferInfo(hout, &binfo);
					if (header == cursor)
					{
						header = temp;
					}
					for (; temp->ch != 0; temp = temp->next)
					{
						putch(temp->ch);
					}
					binfo.dwCursorPosition.X++;
					SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
				}
			}
			putchar('\n');
			char* buf_ptr = buf;
			switch (kbh)
			{
				case 0: *buf_ptr++ = 'm'; break;
				case 1: *buf_ptr++ = 'f'; break;
			}
			kbh = -1;
			switch (buf[0])
			{
			case 'm':
				while (buf_ptr - buf <= BUFLEN && header->ch != 0)
				{
					*buf_ptr++ = header->ch;
					header = header->next;
					delete header->last;
				}
				cc = send(sock, buf, buf_ptr - buf, 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
				if (cc == SOCKET_ERROR)
				{
					printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
					goto quit;
				}
				else if (cc == 0)
				{
					printf("Server closed!"); // 对方正常关闭
					goto quit;
				}
				break;
			case 'f':
				char cmd_buf[BUFLEN + 1];
				int cmd_len = 0;
				char* paras[PARANUM] = {nullptr};
				int para_num = 0;
				while (header->ch == ' ')
				{
					header = header->next;
					delete header->last;
				}
				while (cmd_len <= BUFLEN && header->ch != 0)
				{
					if (header->ch == ' ')
					{
						header = header->next;
						delete header->last;
						while (header->ch == ' ')
						{
							header = header->next;
							delete header->last;
						}
						if (header->ch != 0)
						{
							cmd_buf[cmd_len++] = 0;
							if (para_num < PARANUM)
							{
								paras[para_num++] = cmd_buf + cmd_len;
							}
						}
					}
					else
					{
						cmd_buf[cmd_len++] = header->ch;
						header = header->next;
						delete header->last;
					}
				}
				cmd_buf[cmd_len] = 0;
				if (strcmp(cmd_buf, "quit") == 0)
				{
					if (para_num == 0)
					{
						goto quit;
					}
				}
				else if (strcmp(cmd_buf, "rdir") == 0)
				{
					if (para_num == 1)
					{
						FILE* fp;
						if (access(paras[0], 0) != -1)	//如果文件夹不存在
						{
							strcpy(destdname, paras[0]);
						}
						else if (fopen_s(&fp, destdname, "rb") == NULL)
						{
							puts("不是目录");
						}
						else
						{
							puts("路径不存在");
						}
					}
				}
				else if (strcmp(cmd_buf, "send") == 0)
				{
					if (para_num == 1)
					{
						FILE* srcfile = NULL;
						char srcfname[FNAME_LEN];
						// 打开要写入的二进制文件(w-write b-binary)，没有则创建，有则覆盖
						strcpy(srcfname, paras[0]);
						regex pattern("[^\\/,\\\\]*$", regex::icase);
						//打开要读取的二进制文件(r-read b-binary)
						if (fopen_s(&srcfile, &srcfname[0], "rb") != NULL)
						{
							puts("读取文件未找到！");
							break;
						}
						else
						{
							FileStruct fs;
							smatch result;
							string temp(srcfname);
							if (regex_search(temp, result, pattern))
							{
								strcpy_s(fs.fileName, &((string)result[0])[0]);
							}
							fseek(srcfile, 0, SEEK_END);
							//获取文件的大小
							fs.fileSize = ftell(srcfile);
							fseek(srcfile, 0, SEEK_SET);
							for (int i = 0; i < sizeof(fs); i++)
							{
								*buf_ptr++ = *((char*)&fs + i);
							}
							int len;
							while ((len = fread(buf_ptr, 1, BUFLEN - (buf_ptr - buf), srcfile)) >= BUFLEN - (buf_ptr - buf))
							{
								cc = send(sock, buf, buf_ptr - buf + len, 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
								if (cc == SOCKET_ERROR)
								{
									printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
									goto quit;
								}
								else if (cc == 0)
								{
									printf("Server closed!"); // 对方正常关闭
									goto quit;
								}
								buf_ptr = buf;
							}
							cc = send(sock, buf, buf_ptr - buf + len, 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
							if (cc == SOCKET_ERROR)
							{
								printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
								goto quit;
							}
							else if (cc == 0)
							{
								printf("Server closed!"); // 对方正常关闭
								goto quit;
							}
							fclose(srcfile);
						}
					}
				}
				break;
			}
		}
	}
quit:
	CloseHandle(hThread);
	closesocket(sock); // 关闭监听套接字
	WSACleanup();	   // 卸载winsock library
}
