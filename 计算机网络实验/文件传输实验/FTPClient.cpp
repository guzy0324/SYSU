/* TCPClient.cpp */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <regex>
#include <string>
#include <winsock2.h>
#include <windows.h>
using namespace std;

#define BUFLEN 2000           // 缓冲区大小
#define WSVERS MAKEWORD(2, 0) // 指明版本2.0

#pragma comment(lib, "ws2_32.lib") // 使用winsock 2.0 Llibrary
/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, const char *argv[])
{
    /*控制连接*/
    if (argc != 4)
    {
        puts("Illegal format!");
        return -1;
    }
    WSADATA wsadata;
    WSAStartup(WSVERS, &wsadata); //加载winsock library。WSVERS为请求的版本，wsadata返回系统实际支持的最高版本
    struct hostent *host_temp = gethostbyname(argv[1]);
    system("cls");
    if (host_temp == nullptr)
    {
        printf("Get IP error!");
        return -1;
    }
    char *host = inet_ntoa(*(struct in_addr *)host_temp->h_addr_list[0]); // server IP to connect
    char *service = "21";                                                 // server port to connect
    struct sockaddr_in sin;                                               // an Internet endpoint address
    int cc;                                                               // recv character count
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);       //创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
                                                                   //返回：要监听套接字的描述符或INVALID_SOCKET
    memset(&sin, 0, sizeof(sin));                                  // 从&sin开始的长度为sizeof(sin)的内存清0
    sin.sin_family = AF_INET;                                      // 因特网地址簇
    sin.sin_addr.s_addr = inet_addr(host);                         // 设置服务器IP地址(32位)
    sin.sin_port = htons((u_short)atoi(service));                  // 设置服务器端口号
    int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // 连接到服务器，第二个参数指向存放服务器地址的结构，第三个参数为该结构的大小，返回值为0时表示无错误发生，返回SOCKET_ERROR表示出错，应用程序可通过WSAGetLastError()获取相应错误代码。
    char buf[BUFLEN + 1];
    cc = recv(sock, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
    if (cc == SOCKET_ERROR)
    {
        printf("Error: %d.", GetLastError()); // 出错。其后必须关闭套接字sock
        return -1;
    }

    /*登录*/
    char cmd1[3][BUFLEN + 1] = {{}, {}, "pasv\r\n"};
    char cmd0[2][6] = {"user ", "pass "};
login:
    for (int i = 0; i < 2; i++)
    {
        char temp_buf[BUFLEN + 1];
        printf("%s", cmd0[i]);
        scanf("%s", temp_buf);
        sprintf(cmd1[i], "%s%s\r\n", cmd0[i], temp_buf);
    }
    for (int i = 0; i < 3; i++)
    {
        cc = send(sock, cmd1[i], strlen(cmd1[i]), 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
        if (cc == SOCKET_ERROR)
        {
            printf("Error: %d.", GetLastError()); // 出错。其后必须关闭套接字sock
            return -1;
        }
        else if (cc == 0)
        {
            printf("Server closed!"); // 对方正常关闭
            return -1;
        }
        cc = recv(sock, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
        if (cc == SOCKET_ERROR)
        {
            printf("Error: %d.", GetLastError()); // 出错。其后必须关闭套接字sock
            return -1;
        }
        else if (cc > 0)
        {
            buf[cc] = '\0'; // ensure null-termination
            if (strcmp(buf, "530 User cannot log in.\r\n") == 0)
            {
                printf("%s", buf);
                goto login;
            }
            else if (strcmp(buf, "230 User logged in.\r\n") == 0)
            {
                printf("%s", buf);
            }
        }
    }

    /*数据连接*/
    regex pattern("[0-9]+", regex::icase);
    smatch result;
    string buf_str_temp = (string)buf;
    string::const_iterator iterStart = buf_str_temp.begin();
    string::const_iterator iterEnd = buf_str_temp.end();
    char res[7][4];
    for (int i = 0; i < 7 && regex_search(iterStart, iterEnd, result, pattern); i++)
    {
        strcpy(res[i], &((string)result[0])[0]);
        iterStart = result[0].second; //更新搜索起始位置,搜索剩下的字符串
    }
    u_short service_temp = atoi(res[5]) * 256 + atoi(res[6]); // server IP to connect
    SOCKET sock1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);   //创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
                                                                //返回：要监听套接字的描述符或INVALID_SOCKET
    memset(&sin, 0, sizeof(sin));                               // 从&sin开始的长度为sizeof(sin)的内存清0
    sin.sin_family = AF_INET;                                   // 因特网地址簇
    sin.sin_addr.s_addr = inet_addr(host);                      // 设置服务器IP地址(32位)
    sin.sin_port = htons(service_temp);                         // 设置服务器端口号
    ret = connect(sock1, (struct sockaddr *)&sin, sizeof(sin)); // 连接到服务器，第二个参数指向存放服务器地址的结构，第三个参数为该结构的大小，返回值为0时表示无错误发生，返回SOCKET_ERROR表示出错，应用程序可通过WSAGetLastError()获取相应错误代码。

    /*下载*/
    char retr_cmd[BUFLEN + 1];
    sprintf(retr_cmd, "retr %s\r\n", argv[2]);
    cc = send(sock, retr_cmd, strlen(retr_cmd), 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
    if (cc == SOCKET_ERROR)
    {
        printf("Error: %d.", GetLastError()); // 出错。其后必须关闭套接字sock
        return -1;
    }
    else if (cc == 0)
    {
        printf("Server closed!"); // 对方正常关闭
        return -1;
	}
	while (1)
	{
		cc = recv(sock, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
		if (cc == SOCKET_ERROR)
		{
			printf("Error: %d.", GetLastError()); // 出错。其后必须关闭套接字sock
			return -1;
		}
        buf[cc] = 0;
		if (buf[0] == '5' && buf[1] == '5' && buf[2] == '0')
		{
			printf(buf);
			return -1;
		}
        if (strcmp(buf, "550 The system cannot find the file specified.\r\n") == 0)
		{
			printf(buf);
			return -1;
		}

        else if (strcmp(buf, "226 Transfer complete.\r\n") == 0)
        {
            printf(buf);
			break;
        }
	}
    FILE *fp = fopen(argv[3], "wb");
    if (fp == nullptr)
    {
        printf("Path not exist.");
        return -1;
    }
    while (1)
    {
        cc = recv(sock1, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
        if (cc == SOCKET_ERROR)
        {
            printf("Error: %d.", GetLastError()); // 出错。其后必须关闭套接字sock
            return -1;
        }
        else if (cc == 0)
        {
            break;
        }
        fwrite(buf, cc, 1, fp);
    }
    shutdown(sock1, SD_BOTH);
    closesocket(sock1); // 关闭监听套接字	const char *host = inet_ntoa(*(struct in_addr *)host_temp->h_addr_list[0]); // server IP to connect
    fclose(fp);

    /*退出*/
    cc = send(sock, "quit\r\t", 6, 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
    shutdown(sock, SD_BOTH);
    closesocket(sock); // 关闭监听套接字	const char *host = inet_ntoa(*(struct in_addr *)host_temp->h_addr_list[0]); // server IP to connect
    WSACleanup();      // 卸载winsock library
}