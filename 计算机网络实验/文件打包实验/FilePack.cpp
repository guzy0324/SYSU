#include <iostream>
#include <cstdlib>
#include <cstring>
#include <regex>
using namespace std;
#define BUF_LEN 20
#define FNAME_LEN 300
struct FileStruct {
	char fileName[BUF_LEN];
	__int64 fileSize;
};
int main() {
	FILE* srcfile = NULL;
	FILE* destfile = NULL;
	char buf[20];
	char srcfname[FNAME_LEN];
	char destfname[FNAME_LEN];
	printf("目标文件名：");
	scanf_s("%s", destfname, FNAME_LEN);
	// 打开要写入的二进制文件(w-write b-binary)，没有则创建，有则覆盖
	fopen_s(&destfile, &destfname[0], "wb");
	printf("源文件名：");
	scanf_s("%s", srcfname, FNAME_LEN);
	regex pattern("[^\\/,\\\\]*$", regex::icase);
	while (strcmp(srcfname, "exit") != 0)
	{
		//打开要读取的二进制文件(r-read b-binary)
		if (fopen_s(&srcfile, &srcfname[0], "rb") != NULL) {
			printf("读取文件未找到！\n");
		}
		else {
			int len = 0;
			// fread的参数：缓冲区起始地址，每个数据(char类型)的字节数，最多读出的数据个数，文件句柄
			//      返回值：实际读出的数据个数
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
			fwrite(&fs, sizeof(FileStruct), 1, destfile);
			while ((len = fread(buf, 1, BUF_LEN, srcfile)) >= BUF_LEN) {
				//fwrite的参数：数据起始地址，每个数据(char类型)的字节数，写入数据的个数，文件句柄
				//      返回值：实际写入的数据个数
				fwrite(buf, 1, BUF_LEN, destfile);
			}
			fwrite(buf, 1, len, destfile);   // 写入剩余部分
			fclose(srcfile);
		}
		printf("源文件名：");
		scanf_s("%s", &srcfname[0], FNAME_LEN);
	}
	fclose(destfile);
	return 0;
}