#include<iostream>
#include<string>
using namespace std;
int main() {
	string s1, s2;
	cin >> s1 >> s2;
	int** dp = new int* [s1.length()], i, j, max = 0;
	for (i = 0; i < s1.length(); i++) {
		dp[i] = new int[s2.length()];
		for (j = 0; j < s2.length(); j++) {
			if (s1[i] == s2[j]) {
				if (i == 0 || j == 0) {
					dp[i][j] = 1;
				}
				else {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
			}
			else {
				if (i != 0 && j != 0 && dp[i - 1][j - 1] > max) {
					max = dp[i - 1][j - 1];
				}
				dp[i][j] = 0;
			}
		}
	}
	cout << max;
}
