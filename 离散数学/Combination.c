#include <stdio.h>
#include <stdlib.h>
int n, r;
int **combination;
int fact(int n)
{
    int ans = 1;
    for (; n > 0; n--)
    {
        ans *= n;
    }
    return ans;
}
int main()
{
    scanf("%d", &n);
	scanf("%d", &r);
	if (r > n)
	{
		r = n;
	}
    if (r < 0)
    {
        r = 0;
    }
    int Cnr = fact(n) / (fact(n - r) * fact(r));
	combination = (int **)malloc(Cnr * sizeof(int *));
	combination[0] = (int *)malloc(r * sizeof(int));
    for (int j = 0; j < r; j++)
    {
        combination[0][j] = j + 1;
    }
    for (int i = 1; i < Cnr; i++)
    {
        combination[i] = (int *)malloc(r * sizeof(int));
        for (int j = 0; j < r; j++)
        {
            combination[i][j] = combination[i - 1][j];
        }
		int k = r - 1;
		for (; k >= 0; k--)
		{
			if (combination[i][k] != n - r + k + 1)
			{
                break;
            }
        }
        combination[i][k]++;
        for (int j = k + 1; j < r; j++)
        {
            combination[i][j] = combination[i][j - 1] + 1;
        }
    }
	for (int i = 0; i < Cnr; i++)
	{
		for (int j = 0; j < r - 1; j++)
		{
			printf("%d, ", combination[i][j]);
		}
		printf("%d\n", combination[i][r - 1]);
	}
}