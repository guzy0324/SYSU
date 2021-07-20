#include <stdio.h>
int arr[78];
int top = 0;
int is_prime[78];
int main()
{
    for (int i = 2; i <= 78; i++)
    {
        if (top > 0)
        {
            int j;
            for (j = 0; j < top; j++)
            {
                if (i == i / arr[j] * arr[j])
                {
                    break;
                }
            }
            if (j == top)
            {
                arr[top++] = i;
                is_prime[i] = 1;
            }
        }
        else
        {
            arr[top++] = i;
            is_prime[i] = 1;
        }
    }
    int a = 0;
    int b = 0;
    for (int i = 0; i < top; i++)
    {
        if (is_prime[78 - arr[i]] == 1)
        {
            if (arr[i] * (78 - arr[i]) > a * b)
            {
                a = arr[i];
                b = 78 - arr[i];
            }
        }
    }
    if (a == 0)
    {
        printf("没有a,b");
    }
    else
    {
        printf("a=%d\nb=%d", a, b);
    }
}