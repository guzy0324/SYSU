#include <iostream>
#include <cstdlib>
#include <cstring>
#include <regex>
using namespace std;
#define BUF_LEN 300
#define FNAME_LEN 300
struct FileStruct {
	char fileName[BUF_LEN];
	__int64 fileSize;
};
int main() {
	FILE* srcfile = NULL;
	FILE* destfile = NULL;
	char buf[BUF_LEN];
	char srcfname[FNAME_LEN];
	char destdname[FNAME_LEN];
	char destfname[FNAME_LEN];
	printf("源文件名：");
	scanf_s("%s", srcfname, FNAME_LEN);
	// 打开要写入的二进制文件(w-write b-binary)，没有则创建，有则覆盖
	while (fopen_s(&srcfile, srcfname, "rb") != NULL) {
		printf("读取文件未找到！\n");
		printf("源文件名：");
		scanf_s("%s", srcfname, FNAME_LEN);
	}
	printf("目标文件夹名：");
	scanf_s("%s", destdname, FNAME_LEN);
	while (fopen_s(&destfile, destdname, "rb") == NULL) {
		printf("不是目录\n");
		printf("目标文件夹名：");
		scanf_s("%s", destdname, FNAME_LEN);
	}
	FileStruct fs;
	regex pattern("\\.[^.]*$", regex::icase);
	while (fread(&fs, sizeof(FileStruct), 1, srcfile))
	{
		//打开要读取的二进制文件(r-read b-binary)
		sprintf_s(destfname, "%s/%s", destdname, fs.fileName);
		if (fopen_s(&destfile, destfname, "rb") == NULL) {
			fclose(destfile);
			int i = 1;
			string temp(fs.fileName);
			smatch result;
			string temptemp;
			if (regex_search(temp, result, pattern))
			{
				temptemp = (string)result.prefix();
				sprintf_s(fs.fileName, "%s(%d)%s", &((string)result.prefix())[0], i++, &((string)result[0])[0]);
			}
			sprintf_s(destfname, "%s/%s", destdname, fs.fileName);
			while (fopen_s(&destfile, destfname, "rb") == NULL) {
				fclose(destfile);
				smatch result;
				sprintf_s(fs.fileName, "%s(%d)%s", &((string)result.prefix())[0], i++, &((string)result[0])[0]);
				sprintf_s(destfname, "%s/%s", destdname, fs.fileName);
			}
		}
		fopen_s(&destfile, &destfname[0], "wb");
		__int64 len = fs.fileSize;
		// fread的参数：缓冲区起始地址，每个数据(char类型)的字节数，最多读出的数据个数，文件句柄
		//      返回值：实际读出的数据个数
		while (len >= BUF_LEN) {
			fread(buf, 1, BUF_LEN, srcfile);
			len -= BUF_LEN;
			//fwrite的参数：数据起始地址，每个数据(char类型)的字节数，写入数据的个数，文件句柄
			//      返回值：实际写入的数据个数
			fwrite(buf, 1, BUF_LEN, destfile);
		}
		fread(buf, 1, len, srcfile);
		fwrite(buf, 1, len, destfile);   // 写入剩余部分
		fclose(destfile);
	}
	fclose(srcfile);
	return 0;
}