#include <iostream>
#include <string>
using namespace std;
string src;
string des;
int stt;
int sz;
int main()
{
    scanf("%d", &stt);
    scanf("%d", &sz);
    unsigned char *arr;
    if ((arr = (unsigned char *)malloc(sz)) == NULL)
    {
        puts("马捞C失败！");
        return -1;
    }
    cin >> src >> des;
    FILE *fp;
    if ((fp = fopen((char *)src.c_str(), "rb")) == NULL)
    {
        puts("read失败！");
        return -1;
    }
    fread(arr, 1, sz, fp);
    /*for (int i = 0; i < sz; printf("%c", arr[i++]))
        ;*/
    fclose(fp);
    if ((fp = fopen((char *)des.c_str(), "rb+")) == NULL)
    {
        puts("write失败！");
        return -1;
    }
    fseek(fp, stt, SEEK_SET);
    /*fread(arr, 1, sz, fp);
    for (int i = 0; i < sz; printf("%c", arr[i++]))
        ;*/
    fwrite(arr, 1, sz, fp);
    fclose(fp);
}