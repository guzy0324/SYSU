#include <stdio.h>
int main()
{
    float a = 1;
    float b = 1;
    float c = -1;
    int d = -1;
    float item;
    float ans = 0;
    do
    {
        a *= 1 / 2.0;
        b *= 1 / 3.0;
        c += 2;
        d = -d;
        item = 1 / c * (a + b);
        ans += d * item;
    } while (item >= 0.000001);
    printf("%f", ans);
}