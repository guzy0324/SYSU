#include<iostream>
#include<cstring>
using namespace std;
inline int MAX(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int N, x, y, n, a[10][10], i, j, k, l, dp[10][10][10][10];
    memset(a, 0, sizeof(a));
    memset(dp, 0, sizeof(dp));
    cin >> N;
    while (cin >> x >> y >> n) {
        if (x == 0 && y == 0 && n == 0) {
            break;
        }
        a[x][y] = n;
    }
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            for (k = 1; k <= N; k++) {
                for (l = 1; l <= N; l++) {
                    dp[i][j][k][l] = a[i][j] + MAX(MAX(dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1]), MAX(dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1]));
                    if (i != k || j != l) {
                        dp[i][j][k][l] += a[k][l];
                    }
                }
            }
        } 
    }
    cout << dp[N][N][N][N];
}
