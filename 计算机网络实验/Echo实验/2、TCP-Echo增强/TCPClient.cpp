/* TCPClient.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUFLEN 2000           // ��������С
#define WSVERS MAKEWORD(2, 0) // ָ���汾2.0

#pragma comment(lib, "ws2_32.lib") // ʹ��winsock 2.0 Llibrary
/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
     const char *host = "127.0.0.1"; // server IP to connect
     const char *service = "50500";  // server port to connect
     struct sockaddr_in sin;         // an Internet endpoint address
     char buf[BUFLEN + 1];           // buffer for one line of text
     SOCKET sock;                    // socket descriptor
     int cc;                         // recv character count

     WSADATA wsadata;
     WSAStartup(WSVERS, &wsadata); //����winsock library��WSVERSΪ����İ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾

     sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //�����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
                                                       //���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET

     memset(&sin, 0, sizeof(sin));                                  // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
     sin.sin_family = AF_INET;                                      // ��������ַ��
     sin.sin_addr.s_addr = inet_addr(host);                         // ���÷�����IP��ַ(32λ)
     sin.sin_port = htons((u_short)atoi(service));                  // ���÷������˿ں�
     int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // ���ӵ����������ڶ�������ָ���ŷ�������ַ�Ľṹ������������Ϊ�ýṹ�Ĵ�С������ֵΪ0ʱ��ʾ�޴�����������SOCKET_ERROR��ʾ����Ӧ�ó����ͨ��WSAGetLastError()��ȡ��Ӧ������롣
     
     printf("%s", "����Ҫ���͵���Ϣ��");
     scanf("%s", buf);
     cc = send(sock, buf, strlen(buf), 0); // �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
     putchar('\n');
     if (cc == SOCKET_ERROR)
     {
         printf("Error: %d.\n", GetLastError()); // ����������ر��׽���sock
     }
     else if (cc == 0)
     {
         printf("Server closed!"); // �Է������ر�
     }
     else if (cc > 0)
     {
         cc = recv(sock, buf, BUFLEN, 0); // �ڶ�������ָ�򻺳���������������Ϊ��������С(�ֽ���)�����ĸ�����һ������Ϊ0������ֵ:(>0)���յ����ֽ���,(=0)�Է��ѹر�,(<0)���ӳ���
         if (cc == SOCKET_ERROR)
         {
             printf("Error: %d.\n", GetLastError()); // ����������ر��׽���sock
         }
         else if (cc == 0)
         {
             printf("%s", "Server closed!"); // �Է������ر�
         }
         else if (cc > 0)
         {
             buf[cc] = '\0';    // ensure null-termination
             printf("�յ�����Ϣ��\n%s\n", buf); // ��ʾ�����յ��ַ���
         }
     }
     closesocket(sock); // �رռ����׽���
     WSACleanup();      // ж��winsock library
}
