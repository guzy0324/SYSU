/* server2.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
/* argc: 命令行参数个数， 例如：C:\> TCPServer 8080
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
        struct  sockaddr_in fsin;           	/* the from address of a client       */
        int     msock, ssock;               	/* master & slave sockets         */
        char    *service = "50500";
        struct  sockaddr_in sin;        	/* an Internet endpoint address             */
        int     alen;                       	/* from-address length                      */
        char    *pts;                       	/* pointer to time string           */
        time_t  now;                        	/* current time                                 */

        msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);  	// 创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
                                                           	// 返回：要监听套接字的描述符或INVALID_SOCKET

        memset(&sin,'\0', sizeof(sin));                     	// 从&sin开始的长度为sizeof(sin)的内存清0
        sin.sin_family = AF_INET;                                                       // 因特网地址簇(INET-Internet)
        sin.sin_addr.s_addr = INADDR_ANY;                     	// 监听所有(接口的)IP地址。
        sin.sin_port = htons((u_short)atoi(service));         	// 监听的端口号。atoi--把ascii转化为int，htons--主机序到网络序(host to network，s-short 16位)
        bind(msock, (struct sockaddr *)&sin, sizeof(sin));  	// 绑定监听的IP地址和端口号

        listen(msock, 5);                                   	// 建立长度为5的连接请求队列，并把到来的连接请求加入队列等待处理。

        while(1){                                           	// 检测是否有按键,如果没有则进入循环体执行
           alen = sizeof(struct sockaddr);                	// 取到地址结构的长度
           ssock = accept(msock, (struct sockaddr *)&fsin, &alen); // 如果在连接请求队列中有连接请求，则接受连接请求并建立连接，返回该连接的套接字，否则，本语句被阻塞直到队列非空。fsin包含客户端IP地址和端口号

           time(&now);                                      	// 取得系统时间
           pts =(char *)ctime(&now);                          	// 把时间转换为字符串
          int cc = send(ssock, pts, strlen(pts), 0);      	// 第二个参数指向发送缓冲区，第三个参数为要发送的字节数，第四个参数一般置0，返回值为实际发送的字节数，出错或对方关闭时返回SOCKET_ERROR。
          printf("%s", pts);                                  	// 显示发送的字符串
          close(ssock);                              		// 关闭连接套接字
     }
     close(msock);                                 		// 关闭监听套接字
}