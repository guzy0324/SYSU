#include<iostream>
#include<vector>
using namespace std;
#define MAX_NUM 5001
int n, m, indegree[MAX_NUM], vis[MAX_NUM];
vector<int> E[MAX_NUM];
void dfs(int cur) {
    for (int i = 0; i < E[cur].size(); i++) {
        if (!vis[E[cur][i]]) {
            dfs(E[cur][i]);
        }
        vis[cur] = (vis[cur] + vis[E[cur][i]]) % 80112002;
    }
    if (E[cur].empty()) {
        vis[cur] = 1;
    }
}
int main() {
    cin >> n >> m;
    while(m--) {
        int A, B;
        cin >> A >> B;
        E[A].push_back(B);
        indegree[B]++;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!indegree[i]) {
            dfs(i);
            ans = (ans + vis[i]) % 80112002;
        }
    }
    cout << ans;
}
