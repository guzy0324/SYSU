#include <iostream>
#include <vector>
using namespace std;
pair<int, int> f(int a, int b, int c)
{
	pair<int, int> ans({1, 0});
	int temp = ans.first * b - ans.second * a;
	while (temp != c)
	{
		if (temp <= a)
		{
			ans.first += 1;
			ans.second += 1;
		}
		else
		{
			ans.second += 1;
		}
		temp = ans.first * b - ans.second * a;
	}
	return ans;
}
bool verify(pair<int, int> ans, int a, int b, int c)
{
	return ans.first * b - ans.second * a == c;
}
int main()
{
	int a, b, c;
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);
	if (c == 0)
	{
		return 0;
	}
	pair<int, int> ans;
	if (a > b)
	{
		ans = f(b, a, c);
		if (verify(ans, b, a, c))
		{
			puts("true");
		}
		else
		{
			puts("false");
		}
	}
	else
	{
		ans = f(a, b, c);
		if (verify(ans, a, b, c))
		{
			puts("true");
		}
		else
		{
			puts("false");
		}
	}
}