/* TCPClient.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUFLEN 2000          // 缓冲区大小
#define WSVERS MAKEWORD(2, 0) // 指明版本2.0

#pragma comment(lib, "ws2_32.lib") // 使用winsock 2.0 Llibrary
/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
     const char *host = "202.116.64.201"; // server IP to connect
     const char *service = "80";  // server port to connect
     struct sockaddr_in sin;         // an Internet endpoint address
     char buf[BUFLEN + 1];           // buffer for one line of text
     SOCKET sock;                    // socket descriptor
     int cc;                         // recv character count

     WSADATA wsadata;
     WSAStartup(WSVERS, &wsadata); //加载winsock library。WSVERS为请求的版本，wsadata返回系统实际支持的最高版本

     sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
                                                       //返回：要监听套接字的描述符或INVALID_SOCKET

     memset(&sin, 0, sizeof(sin));                                  // 从&sin开始的长度为sizeof(sin)的内存清0
     sin.sin_family = AF_INET;                                      // 因特网地址簇
     sin.sin_addr.s_addr = inet_addr(host);                         // 设置服务器IP地址(32位)
     sin.sin_port = htons((u_short)atoi(service));                  // 设置服务器端口号
     int ret = connect(sock, (struct sockaddr *)&sin, sizeof(sin)); // 连接到服务器，第二个参数指向存放服务器地址的结构，第三个参数为该结构的大小，返回值为0时表示无错误发生，返回SOCKET_ERROR表示出错，应用程序可通过WSAGetLastError()获取相应错误代码。
	 strcpy(buf, "GET / HTTP/1.1\r\n");
     //strcat(buf, "Connection:keep-alive\r\n");
     strcat(buf, "Connection:close\r\n");
     strcat(buf, "Host:sdcs.sysu.edu.cn\r\n");
     strcat(buf, "Range: bytes=100-200,400-\r\n");
     strcat(buf, "\r\n");
	 /*strcat(buf, "GET /sites/sdcs.live1.dpcms8.sysu.edu.cn/files/styles/slideshow/public/slideshow/frontpic1.jpg?itok=W4EQ5ELH HTTP/1.1\r\n");
	 //strcpy(buf, "GET /sites/sdcs.live1.dpcms8.sysu.edu.cn/files/styles/slideshow/public/slideshow/frontpic1.jpg?itok=W4EQ5ELH HTTP/1.1\r\n");
     strcat(buf, "Connection:close\r\n");
     strcat(buf, "Host:sdcs.sysu.edu.cn\r\n");
     //strcat(buf, "If-Modified-Since: Fri, 16 Jan  2019 13:22:17 GMT\r\n");
     strcat(buf, "\r\n");*/
     printf("http请求：\n%s", buf);
	 cc = send(sock, buf, strlen(buf), 0); // 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值：>=0 实际发送的字节数，0 对方正常关闭，SOCKET_ERROR 出错。
     if (cc == SOCKET_ERROR)
     {
         printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
     }
     else if (cc == 0)
     {
         printf("Server closed!"); // 对方正常关闭
     }
     else if (cc > 0)
     {
         puts("HTTP响应：");
         while (1) {
             cc = recv(sock, buf, BUFLEN, 0); // 第二个参数指向缓冲区，第三个参数为缓冲区大小(字节数)，第四个参数一般设置为0，返回值:(>0)接收到的字节数,(=0)对方已关闭,(<0)连接出错
             if (cc == SOCKET_ERROR)
             {
                 printf("Error: %d.\n", GetLastError()); // 出错。其后必须关闭套接字sock
                 break;
             }
             else if (cc == 0)
             {
                 printf("%s", "Server closed!"); // 对方正常关闭
                 break;
             }
             else if (cc > 0)
             {
                 buf[cc] = '\0';    // ensure null-termination
                 printf("%s\n", buf); // 显示所接收的字符串
             }
         }
     }
     closesocket(sock); // 关闭监听套接字
     WSACleanup();      // 卸载winsock library
}
