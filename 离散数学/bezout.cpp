#include <iostream>
#include <vector>
using namespace std;
vector<int> A, B;
int get_gcd(int a, int b)
{
	A.push_back(a);
	B.push_back(b);
	if (a == 0)
	{
		return b;
	}
	return get_gcd(b % a, a);
}
pair<int, int> get_bezout()
{
	pair<int, int> bezout(0, 1);
	A.pop_back();
	B.pop_back();
	while (!A.empty())
	{
		int s = bezout.first;
		int t = bezout.second;
		int k = B.back() / A.back();
		bezout.first = t - k * s;
		bezout.second = s;
		A.pop_back();
		B.pop_back();
	}
	return bezout;
}
inline bool verify(int a, int b, int gcd, pair<int, int> bezout)
{
	return gcd == a * bezout.first + b * bezout.second;
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
	int gcd = get_gcd(a, b);
	pair<int, int> bezout = get_bezout();
	if (verify(a, b, gcd, bezout))
	{
		puts("true");
	}
	else
	{
		puts("false");
	}
}