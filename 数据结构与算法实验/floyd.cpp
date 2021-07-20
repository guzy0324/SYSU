#include<iostream>
#include<vector>
using namespace std;
#define MAXN 100
int n, E[MAXN][MAXN];
struct t {
    int distance;
    vector<int> path;
} dp[MAXN][MAXN];
void floyd() {
    int i, j, k;
    vector<int>::iterator iter;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                if (dp[j][k].distance > dp[j][i].distance + dp[i][k].distance) {
                    dp[j][k].distance = dp[j][i].distance + dp[i][k].distance;
                    dp[j][k].path = dp[j][i].path;
                    for (iter = dp[i][k].path.begin() + 1; iter != dp[i][k].path.end(); iter++) {
                        dp[j][k].path.push_back(*iter);
                    }
                }
            }
        }
    }
}
int main() {
    cin >> n;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cin >> E[i][j];
            dp[i][j].distance = E[i][j];
            dp[i][j].path = {i, j};
        }
    }
    floyd();
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << dp[i][j].distance << ' ';
        }
        cout << endl;
    }
    vector<int>::iterator iter;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (iter = dp[i][j].path.begin(); iter != dp[i][j].path.end(); iter++) {
                cout << char(*iter + 'a') << ' ';
            }
            cout << endl;
        }
    }
}
