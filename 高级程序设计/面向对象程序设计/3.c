#include <stdio.h>
#include <stdlib.h>
int n;
int *arr;
void sort(int *arr, int l, int r)
{
    int p1 = l, p2 = r, pivot = arr[l];
    while (p1 < p2)
    {
        while (arr[p2] > pivot && p1 < p2)
        {
            p2--;
        }
        arr[p1] = arr[p2];
        while (arr[p1] <= pivot && p1 < p2)
        {
            p1++;
        }
        arr[p2] = arr[p1];
    }
    arr[p1] = pivot;
    if (l < p1 - 1)
    {
        sort(arr, l, p1 - 1);
    }
    if (p1 + 1 < r)
    {
        sort(arr, p1 + 1, r);
    }
}
int main()
{
    printf("输入学生数（类型是int型）：");
    scanf("%d", &n);
    printf("输入%d个学生的成绩（用空格或回车分隔）：", n);
    arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    printf("%d个学生的平均成绩是%f\n", n, sum / n);
    int A = 0, B = 0, C = 0, D = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= 85)
        {
            A += 1;
        }
        else if (arr[i] >= 70)
        {
            B += 1;
        }
        else if (arr[i] >= 60)
        {
            C += 1;
        }
        else
        {
            D += 1;
        }
    }
    printf("%d个学生中，A等有%d人，B等有%d人，C等有%d人，D等有%d人\n", n, A, B, C, D);
    sort(arr, 0, n - 1);
    printf("%d个学生中，最大值是%d，最小值是%d\n", n, arr[n - 1], arr[0]);
    if (n % 2 == 0)
    {
        printf("%d个学生中，中位数是%f", n, (arr[n / 2 - 1] + arr[n / 2]) / 2.0);
    }
    else
    {
        printf("%d个学生中，中位数是%d", n, arr[n / 2 - 1]);
    }
}