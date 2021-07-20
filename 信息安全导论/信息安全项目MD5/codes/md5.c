#include <stdio.h>
#include <string.h>

#define A(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define B(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define C(x, y, z) ((x) ^ (y) ^ (z))
#define D(x, y, z) ((y) ^ ((x) | (~z)))

#define RL(x, y) (((x) << (y)) | ((x) >> (32 - (y)))) //x向左循环移y位

#define PP(x) (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24) //将x高低位互换,例如PP(aabbccdd)=ddccbbaa

#define AA(p, q, r, s, M, x, y) p = q + (RL((p + A(q, r, s) + M + y), x))
#define BB(p, q, r, s, M, x, y) p = q + (RL((p + B(q, r, s) + M + y), x))
#define CC(p, q, r, s, M, x, y) p = q + (RL((p + C(q, r, s) + M + y), x))
#define DD(p, q, r, s, M, x, y) p = q + (RL((p + D(q, r, s) + M + y), x))

unsigned P, Q, R, S, p, q, r, s, i, j, len, flen[2], M[16]; //len文件长, flen[2]为64位二进制表示的文件初始长度
FILE *fp;

void md5()
{
    p = P, q = Q, r = R, s = S;
    // Round 1
    AA(p, q, r, s, M[0], 7, 0xd76aa478);   // 1
    AA(s, p, q, r, M[1], 12, 0xe8c7b756);  // 2
    AA(r, s, p, q, M[2], 17, 0x242070db);  // 3
    AA(q, r, s, p, M[3], 22, 0xc1bdceee);  // 4
    AA(p, q, r, s, M[4], 7, 0xf57c0faf);   // 5
    AA(s, p, q, r, M[5], 12, 0x4787c62a);  // 6
    AA(r, s, p, q, M[6], 17, 0xa8304613);  // 7
    AA(q, r, s, p, M[7], 22, 0xfd469501);  // 8
    AA(p, q, r, s, M[8], 7, 0x698098d8);   // 9
    AA(s, p, q, r, M[9], 12, 0x8b44f7af);  // 10
    AA(r, s, p, q, M[10], 17, 0xffff5bb1); // 11
    AA(q, r, s, p, M[11], 22, 0x895cd7be); // 12
    AA(p, q, r, s, M[12], 7, 0x6b901122);  // 13
    AA(s, p, q, r, M[13], 12, 0xfd987193); // 14
    AA(r, s, p, q, M[14], 17, 0xa679438e); // 15
    AA(q, r, s, p, M[15], 22, 0x49b40821); // 16

    // Round 2
    BB(p, q, r, s, M[1], 5, 0xf61e2562);   // 17
    BB(s, p, q, r, M[6], 9, 0xc040b340);   // 18
    BB(r, s, p, q, M[11], 14, 0x265e5a51); // 19
    BB(q, r, s, p, M[0], 20, 0xe9b6c7aa);  // 20
    BB(p, q, r, s, M[5], 5, 0xd62f105d);   // 21
    BB(s, p, q, r, M[10], 9, 0x02441453);  // 22
    BB(r, s, p, q, M[15], 14, 0xd8a1e681); // 23
    BB(q, r, s, p, M[4], 20, 0xe7d3fbc8);  // 24
    BB(p, q, r, s, M[9], 5, 0x21e1cde6);   // 25
    BB(s, p, q, r, M[14], 9, 0xc33707d6);  // 26
    BB(r, s, p, q, M[3], 14, 0xf4d50d87);  // 27
    BB(q, r, s, p, M[8], 20, 0x455a14ed);  // 28
    BB(p, q, r, s, M[13], 5, 0xa9e3e905);  // 29
    BB(s, p, q, r, M[2], 9, 0xfcefa3f8);   // 30
    BB(r, s, p, q, M[7], 14, 0x676f02d9);  // 31
    BB(q, r, s, p, M[12], 20, 0x8d2a4c8a); // 32

    // Round 3
    CC(p, q, r, s, M[5], 4, 0xfffa3942);   // 33
    CC(s, p, q, r, M[8], 11, 0x8771f681);  // 34
    CC(r, s, p, q, M[11], 16, 0x6d9d6122); // 35
    CC(q, r, s, p, M[14], 23, 0xfde5380c); // 36
    CC(p, q, r, s, M[1], 4, 0xa4beea44);   // 37
    CC(s, p, q, r, M[4], 11, 0x4bdecfa9);  // 38
    CC(r, s, p, q, M[7], 16, 0xf6bb4b60);  // 39
    CC(q, r, s, p, M[10], 23, 0xbebfbc70); // 40
    CC(p, q, r, s, M[13], 4, 0x289b7ec6);  // 41
    CC(s, p, q, r, M[0], 11, 0xeaa127fa);  // 42
    CC(r, s, p, q, M[3], 16, 0xd4ef3085);  // 43
    CC(q, r, s, p, M[6], 23, 0x04881d05);  // 44
    CC(p, q, r, s, M[9], 4, 0xd9d4d039);   // 45
    CC(s, p, q, r, M[12], 11, 0xe6db99e5); // 46
    CC(r, s, p, q, M[15], 16, 0x1fa27cf8); // 47
    CC(q, r, s, p, M[2], 23, 0xc4ac5665);  // 48

    // Round 4
    DD(p, q, r, s, M[0], 6, 0xf4292244);   // 49
    DD(s, p, q, r, M[7], 10, 0x432aff97);  // 50
    DD(r, s, p, q, M[14], 15, 0xab9423a7); // 51
    DD(q, r, s, p, M[5], 21, 0xfc93a039);  // 52
    DD(p, q, r, s, M[12], 6, 0x655b59c3);  // 53
    DD(s, p, q, r, M[3], 10, 0x8f0ccc92);  // 54
    DD(r, s, p, q, M[10], 15, 0xffeff47d); // 55
    DD(q, r, s, p, M[1], 21, 0x85845dd1);  // 56
    DD(p, q, r, s, M[8], 6, 0x6fa87e4f);   // 57
    DD(s, p, q, r, M[15], 10, 0xfe2ce6e0); // 58
    DD(r, s, p, q, M[6], 15, 0xa3014314);  // 59
    DD(q, r, s, p, M[13], 21, 0x4e0811a1); // 60
    DD(p, q, r, s, M[4], 6, 0xf7537e82);   // 61
    DD(s, p, q, r, M[11], 10, 0xbd3af235); // 62
    DD(r, s, p, q, M[2], 15, 0x2ad7d2bb);  // 63
    DD(q, r, s, p, M[9], 21, 0xeb86d391);  // 64

    P += p;
    Q += q;
    R += r;
    S += s;
}

int main(int argc, char *argv[])
{
    for (j = 1; j < argc; j++)
    {
        if (!(fp = fopen(argv[j], "rb")))
        {
            puts("Can not open this file!");
            continue;
        }                       //以二进制打开文件
        fseek(fp, 0, SEEK_END); //文件指针转到文件末尾
        if ((len = ftell(fp)) == -1)
        {
            puts("Sorry! Can not calculate files which larger than 2 GB!");
            fclose(fp);
            continue;
        } //ftell函数返回long,最大为2GB,超出返回-1
        rewind(fp);
        P = 0x67452301, Q = 0xefcdab89, R = 0x98badcfe, S = 0x10325476;
        flen[1] = len / 0x20000000; //flen单位是bit
        flen[0] = (len % 0x20000000) * 8;
        memset(M, 0, 64);
        fread(&M, 4, 16, fp);
        for (i = 0; i < len / 64; i++)
        {
            md5();
            memset(M, 0, 64);
            fread(&M, 4, 16, fp);
        }
        ((char *)M)[len % 64] = 128; //文件结束补1,补0操作,128二进制即10000000
        if (len % 64 > 55)
            md5(), memset(M, 0, 64);
        memcpy(M + 14, flen, 8); //文件末尾加入原文件的bit长度
        md5();
        fclose(fp);
        printf("%08x%08x%08x%08x\n", PP(P), PP(Q), PP(R), PP(S)); //高低位逆反输出
    }
}
