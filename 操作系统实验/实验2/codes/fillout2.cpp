#include <iostream>
#include <string>
using namespace std;
unsigned char arr[512];
string src;
string des;
int stt;
int sz;
int main()
{
	scanf("%d", &stt);
	scanf("%d", &sz);
    cin >> src >> des;
    FILE *fp = fopen((char *)src.c_str(), "rb");
    fread(arr, 1, sz, fp);
    /*for (int i = 0; i < sz; printf("%c", arr[i++]))
        ;*/
    fclose(fp);
    fp = fopen((char *)des.c_str(), "rb+");
    fseek(fp, stt, SEEK_SET);
    /*fread(arr, 1, sz, fp);
    for (int i = 0; i < sz; printf("%c", arr[i++]))
        ;*/
    fwrite(arr, 1, sz, fp);
    fclose(fp);
}