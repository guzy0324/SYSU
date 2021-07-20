#include <stdio.h>
#include <stdlib.h>
int n;
int **permutation;
int fact(int n)
{
    int ans = 1;
    for (; n > 0; n--)
    {
        ans *= n;
    }
    return ans;
}
void swap(int *a, int *b)
{
    *a += *b;
    *b = *a - *b;
    *a -= *b;
}
void quick_sort(int l, int r, int *a)
{
	if (l >= r)
	{
		return;
	}
	int pivot = a[l], i = l, j = r;
	while (i < j)
	{
		while (i < j && a[j] > pivot)
		{
			j--;
		}
		if (i < j)
		{
			a[i] = a[j];
		}
		while (i < j && a[i] <= pivot)
		{
			i++;
		}
		if (i < j)
		{
			a[j] = a[i];
		}
	}
	a[i] = pivot;
	quick_sort(l, i - 1, a);
	quick_sort(i + 1, r, a);
}
int main()
{
    scanf("%d", &n);
    int Pnn = fact(n);
    permutation = (int **)malloc(Pnn * sizeof(int *));
    permutation[0] = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++)
    {
        permutation[0][j] = j + 1;
    }
    for (int i = 1; i < Pnn; i++)
    {
        permutation[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            permutation[i][j] = permutation[i - 1][j];
        }
        int m = n - 1;
        for (; m >= 1; m--)
        {
            if (permutation[i][m - 1] < permutation[i][m])
            {
                break;
            }
        }
        int l = m;
        for (; l < n; l++)
        {
            if (permutation[i][l] - permutation[i][m - 1] < 0)
            {
                break;
            }
        }
        swap(&permutation[i][m - 1], &permutation[i][l - 1]);
		quick_sort(m, n - 1, permutation[i]);
    }
	for (int i = 0; i < Pnn; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			printf("%d, ", permutation[i][j]);
		}
		printf("%d\n", permutation[i][n - 1]);
	}
}
