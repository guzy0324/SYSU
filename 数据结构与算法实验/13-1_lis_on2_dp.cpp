#include<iostream>
#include<algorithm>
using namespace std;
#define MAX_NUM 101
int n, a[MAX_NUM], dp[MAX_NUM], ans = 0;
int main() {
    cin >> n;
    int i, j;
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    dp[n] = 0;
    for (i = n - 1; i >= 0; i--) {
        for (j = 1; i + j < n && a[i + j] <= a[i]; j++);
        dp[i] = dp[i + j] + 1;
        ans = max(dp[i], ans);
    }
    cout << ans;
}
