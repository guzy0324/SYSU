#include <iostream>
using namespace std;
int gcd;
int s, t;
void euclid(int a, int b)
{
	if (a == 0)
	{
		gcd = b;
		s = 0;
		t = 1;
		return;
	}
	euclid(b % a, a);
	int s_temp = s;
	s = t - b / a * s;
	t = s_temp;
}
inline bool verify(int a, int b)
{
	return gcd == a * s + b * t;
}
int main()
{
	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);
	if (a > b)
	{
		a += b;
		b = a - b;
		a -= b;
	}
	euclid(a, b);
	if (verify(a, b))
	{
		puts("true");
	}
	else
	{
		puts("false");
	}
}