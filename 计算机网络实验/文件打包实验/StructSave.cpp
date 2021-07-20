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
	// 打开要写的二进制文件(w-write b-binary)，没有则创建，有则覆盖
	if ((fopen_s(&fp, "F:\\temp\\aaa.stru", "wb")) != NULL) {
		printf("cant open the file!\n");
		getchar();
		exit(0);
	}
	Person per;
	printf("username: ");
	scanf_s("%s", per.username, NAME_LEN);
	while (strcmp(per.username, "exit") != 0)
	{
		printf("level: ");
		scanf_s("%d", &per.level);
		printf("email: ");
		scanf_s("%s", per.email, EMAIL_LEN);
		time(&per.sendtime);
		time(&per.regtime);
		//fwrite的参数：数据的起始地址，每个数据的所占字节数，要写入的数据个数，文件句柄
		//      返回值：实际写入的数据个数
		if (fwrite(&per, sizeof(Person), 1, fp) != 1) {
			printf("file write error!\n");
		}
		printf("\r\nusername: ");
		scanf_s("%s", per.username, NAME_LEN);
	}
	fclose(fp);
	return 0;
}
