/*
  本文件把三个结构变量值写入文件，然后再从该文件中读出这些值并显示出来
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NAME_LEN 30
#define EMAIL_LEN 30
#define BUF_LEN 30
struct Person
{
	char username[NAME_LEN];	// 员工名
	int level;				// 工资级别
	char email[EMAIL_LEN];	// email地址
	time_t sendtime;		// 发送时间
	time_t regtime;			// 注册时间
}; 
int main()
{
	FILE * fp;
	Person per;
	if (fopen_s(&fp, "F:\\temp\\aaa.stru", "rb") != NULL) {
		getchar();
		printf("can't open the file!\n");
		exit(0);
	}
	// fread的参数：缓冲区起始地址，每个数据的字节数，可缓存的数据个数，文件句柄
	//      返回值：实际读出的数据个数
	while (fread(&per, sizeof(Person), 1, fp) == 1)
	{
		printf("username: %s\r\n", per.username);
		printf("level: %d\r\n", per.level);
		printf("email: %s\r\n", per.email);
		char buf[BUF_LEN];
		ctime_s(buf, BUF_LEN, &per.sendtime);
		printf("sendtime: %s", buf);
		ctime_s(buf, BUF_LEN, &per.regtime);
		printf("regtime: %s\r\n", buf);
	}
	return 0;
}
