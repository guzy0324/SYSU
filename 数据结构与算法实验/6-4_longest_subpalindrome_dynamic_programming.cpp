#include<iostream>
#include<string>
using namespace std;
int main() {
    string s;
    cin >> s;
    int** dp = new int* [s.length()], i, j, max_i, max_j, max = 0;       
    for (i = 0; i < s.length(); i++) {
        dp[i] = new int[s.length()];
        for (j = 0; j < s.length(); j++) {
            if (s[i] == s[s.length() - 1 - j]) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                }
                else {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                if ((i == s.length() - 1 || j == s.length() - 1) && dp[i][j] > max) {
                    max = dp[i][j];
                    max_i = i;
                    max_j = j;
                }
            }
            else {
                if (i != 0 && j != 0 && dp[i - 1][j - 1] > max) {
                    max = dp[i - 1][j - 1];
                    max_i = i - 1;
                    max_j = j - 1;              
                }
                dp[i][j] = 0;
            }
        }
    }
    for (i = s.length() - 1 - max_j; i <= max_i; i++) {
        cout << s[i];
    }
}
