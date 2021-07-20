/* UDPClient.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUFLEN 2000				   // ��������С
#define WSVERS MAKEWORD(2, 2)	   // ָ���汾2.2
#pragma comment(lib, "ws2_32.lib") // ����winsock 2.2 Llibrary

int main(int argc, char *argv[])
{
	const char *host = "127.0.0.1"; // server IP to connect
	const char *service = "50500";	// server port to connect
	struct sockaddr_in toAddr;		// an Internet endpoint address
	char buf[BUFLEN + 1];			// buffer for one line of text
	SOCKET sock;					// socket descriptor
	int cc;							// recv character count

	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata); // ����ĳ�汾Socket��DLL

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(service)); //atoi����asciiת��Ϊint. htons��������(host)ת��Ϊ������(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);		 //���hostΪ��������Ҫ���ú���gethostbyname������ת��ΪIP��ַ

	printf("%s", "����Ҫ���͵���Ϣ��");
	scanf("%s", buf);

	cc = sendto(sock, buf, strlen(buf), 0, (SOCKADDR *)&toAddr, sizeof(toAddr));
	putchar('\n');
	if (cc == SOCKET_ERROR)
	{
		printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
	}
	else
	{
		int temp = sizeof(toAddr);
		cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&toAddr, &temp); //���շ��������ݡ����ؽ����ccΪ���յ��ַ�����toAddr�н�����������IP��ַ�Ͷ˿ںš�
		if (cc == SOCKET_ERROR)
		{
			printf("recvfrom() failed; %d\n", WSAGetLastError());
		}
		else if (cc > 0)
		{
			buf[cc] = '\0';					   // ensure null-termination
			printf("�յ�����Ϣ��\n%s\n", buf); // ��ʾ�����յ��ַ���
		}
	}

	closesocket(sock);
	WSACleanup(); // ж��ĳ�汾��DLL
}
