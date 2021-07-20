#include <iostream>
#include<string>
using namespace std;
inline int MAX(int a, int b) {
    return a > b ? a : b;
}
int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int dp[s1.length()][s2.length()], i, j;
    for (i = 0; i < s1.length(); i++) {
        for (j = 0; j < s2.length(); j++) {
            if (s1[i] == s2[j]) {
                if (j == 0 || i == 0) {
                    dp[i][j] = 1;
                }
                else {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
            }
            else {
                if (j == 0) {
                    if (i == 0) {
                        dp[i][j] = 0;
                    }
                    else {
                        dp[i][j] = dp[i - 1][j];
                    }
                }
                else if (i == 0) {
                    dp[i][j] = dp[i][j - 1];
                }
                else {
                    dp[i][j] = MAX(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
    }
    cout << dp[s1.length() - 1][s2.length() - 1];
}
