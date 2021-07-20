#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
#define SIZE 100
int n, m, E[SIZE][SIZE], degree[SIZE], odd, vis[SIZE], ans;
vector<int> G[SIZE];
void dfs(int cur, int start) {
    int i;
    for (i = 1; i <= n; i++) {
        if (!vis[i] && E[cur][i]) {
            vis[i] = 1;
            G[start].push_back(i);
            dfs(i, start);
        }
    }
}
int main() {
    int a, b;
    cin >> n >> m;
    memset(degree, 0, sizeof(degree));
    memset(E, 0, sizeof(E));
    memset(vis, 0, sizeof(vis));
    for (; m; m--) {
        cin >> a >> b;
        E[a][b] = 1;
        E[b][a] = 1;
        degree[a]++;
        degree[b]++;
    }
    for (a = 1; a <= n; a++) {
        if (!vis[a]) {
            vis[a] = 1;
            G[a].push_back(a);
            dfs(a, a);
        }
    }
    for (a = 1, ans = 0; a <= n; a++) {
        if (G[a].size() > 1) {    
            for (b = 0, odd = 0; b < G[a].size(); b++) {    
                if (degree[G[a][b]] % 2) {
                    odd++;
                }
            }
            ans += max(odd / 2, 1);
        }
    }
    cout << ans;
}
