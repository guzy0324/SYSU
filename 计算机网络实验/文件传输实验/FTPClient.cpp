/* TCPClient.cpp */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <regex>
#include <string>
#include <winsock2.h>
#include <windows.h>
using namespace std;

#define BUFLEN 2000           // ��������С
#define WSVERS MAKEWORD(2, 0) // ָ���汾2.0

#pragma comment(lib, "ws2_32.lib") // ʹ��winsock 2.0 Llibrary
/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, const char *argv[])
{
    /*��������*/
    if (argc != 4)
    {
        puts("Illegal format!");
        return -1;
    }
    WSADATA wsadata;
    WSAStartup(WSVERS, &wsadata); //����winsock library��WSVERSΪ����İ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
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
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);       //�����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
                                                                   //���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET
    memset(&sin, 0, sizeof(sin));                                  // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
    sin.sin_family = AF_INET;                                      // ��������ַ��
    sin.sin_addr.s_addr = inet_addr(host);                         // ���÷�����IP��ַ(32λ)
    sin.sin_port = htons((u_short)atoi(service));                  // ���÷������˿ں�
    int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // ���ӵ����������ڶ�������ָ���ŷ�������ַ�Ľṹ������������Ϊ�ýṹ�Ĵ�С������ֵΪ0ʱ��ʾ�޴�����������SOCKET_ERROR��ʾ����Ӧ�ó����ͨ��WSAGetLastError()��ȡ��Ӧ������롣
    char buf[BUFLEN + 1];
    cc = recv(sock, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
    if (cc == SOCKET_ERROR)
    {
        printf("Error: %d.", GetLastError()); // ����������ر��׽���sock
        return -1;
    }

    /*��¼*/
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
        cc = send(sock, cmd1[i], strlen(cmd1[i]), 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
        if (cc == SOCKET_ERROR)
        {
            printf("Error: %d.", GetLastError()); // ����������ر��׽���sock
            return -1;
        }
        else if (cc == 0)
        {
            printf("Server closed!"); // �Է������ر�
            return -1;
        }
        cc = recv(sock, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
        if (cc == SOCKET_ERROR)
        {
            printf("Error: %d.", GetLastError()); // ����������ر��׽���sock
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

    /*��������*/
    regex pattern("[0-9]+", regex::icase);
    smatch result;
    string buf_str_temp = (string)buf;
    string::const_iterator iterStart = buf_str_temp.begin();
    string::const_iterator iterEnd = buf_str_temp.end();
    char res[7][4];
    for (int i = 0; i < 7 && regex_search(iterStart, iterEnd, result, pattern); i++)
    {
        strcpy(res[i], &((string)result[0])[0]);
        iterStart = result[0].second; //����������ʼλ��,����ʣ�µ��ַ���
    }
    u_short service_temp = atoi(res[5]) * 256 + atoi(res[6]); // server IP to connect
    SOCKET sock1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);   //�����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
                                                                //���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET
    memset(&sin, 0, sizeof(sin));                               // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
    sin.sin_family = AF_INET;                                   // ��������ַ��
    sin.sin_addr.s_addr = inet_addr(host);                      // ���÷�����IP��ַ(32λ)
    sin.sin_port = htons(service_temp);                         // ���÷������˿ں�
    ret = connect(sock1, (struct sockaddr *)&sin, sizeof(sin)); // ���ӵ����������ڶ�������ָ���ŷ�������ַ�Ľṹ������������Ϊ�ýṹ�Ĵ�С������ֵΪ0ʱ��ʾ�޴�����������SOCKET_ERROR��ʾ����Ӧ�ó����ͨ��WSAGetLastError()��ȡ��Ӧ������롣

    /*����*/
    char retr_cmd[BUFLEN + 1];
    sprintf(retr_cmd, "retr %s\r\n", argv[2]);
    cc = send(sock, retr_cmd, strlen(retr_cmd), 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
    if (cc == SOCKET_ERROR)
    {
        printf("Error: %d.", GetLastError()); // ����������ر��׽���sock
        return -1;
    }
    else if (cc == 0)
    {
        printf("Server closed!"); // �Է������ر�
        return -1;
	}
	while (1)
	{
		cc = recv(sock, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
		if (cc == SOCKET_ERROR)
		{
			printf("Error: %d.", GetLastError()); // ����������ر��׽���sock
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
        cc = recv(sock1, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
        if (cc == SOCKET_ERROR)
        {
            printf("Error: %d.", GetLastError()); // ����������ر��׽���sock
            return -1;
        }
        else if (cc == 0)
        {
            break;
        }
        fwrite(buf, cc, 1, fp);
    }
    shutdown(sock1, SD_BOTH);
    closesocket(sock1); // �رռ����׽���	const char *host = inet_ntoa(*(struct in_addr *)host_temp->h_addr_list[0]); // server IP to connect
    fclose(fp);

    /*�˳�*/
    cc = send(sock, "quit\r\t", 6, 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
    shutdown(sock, SD_BOTH);
    closesocket(sock); // �رռ����׽���	const char *host = inet_ntoa(*(struct in_addr *)host_temp->h_addr_list[0]); // server IP to connect
    WSACleanup();      // ж��winsock library
}