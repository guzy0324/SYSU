#include<iostream>
#include<vector>
using namespace std;
#define MAXN 100
int n, E[MAXN][MAXN];
struct t {
    int distance;
    vector<int> path;
} dp[MAXN], ans[MAXN];
void dijkstra() {
    int i, j, k;
    ans[0].path.push_back(0);
    for (i = 1; i <= n - 1; i++) {
        for (k = 0; !dp[k].distance; k++);
        for (j = k + 1; j < n; j++) {
            if (dp[j].distance && dp[k].distance > dp[j].distance) {
                k = j;
            }
        }
        for (j = 1; j < n; j++) {
            if (dp[j].distance > dp[k].distance + E[k][j]) {
                dp[j].distance = dp[k].distance + E[k][j];
                dp[j].path = dp[k].path;
                dp[j].path.push_back(j);
            }
        }
        ans[k] = dp[k];
        dp[k].distance = 0;
    }
}
int main() {
    cin >> n;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cin >> E[i][j];
        }
        dp[i].distance = E[0][i];
        dp[i].path = {0, i};
    }
    dijkstra();
    for (i = 0; i < n; i++) {
        cout << ans[i].distance << ' ';
    }
    cout << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < ans[i].path.size(); j++) {
            cout << ans[i].path[j] << ' ';
        }
        cout << endl;
    }
}
