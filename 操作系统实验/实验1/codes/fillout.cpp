#include <iostream>
#include <string>
using namespace std;
unsigned char arr[512];
string src;
string des;
int main()
{
    cin >> src >> des;
    FILE *fp = fopen((char *)src.c_str(), "rb");
    fread(arr, 1, 512, fp);
    /*for (int i = 0; i < 512; printf("%c", arr[i++]))
        ;*/
    fclose(fp);
    fp = fopen((char *)des.c_str(), "rb+");
    /*fread(arr, 1, 512, fp);
    for (int i = 0; i < 512; printf("%c", arr[i++]))
        ;*/
    fwrite(arr, 1, 512, fp);
    fclose(fp);
}