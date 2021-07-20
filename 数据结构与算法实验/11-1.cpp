/*
反向存边，然后标号从大到小向外便利。
如果遇到了一个之前已经遍历过的店，则不需要继续前进。
因为再往前走，那些点的答案都会由之前第一次遍历到它们的起点贡献。
复杂度O(n+m)。
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define SIZE 10007
int N, M, vis[SIZE], Max;
vector<int> E[SIZE];
void dfs(int u, int end) {
    Max = max(Max, u);
    int i;
    for (i = 0; i < E[u].size(); i++) {
        if (!vis[E[u][i]]) {
            vis[E[u][i]] = end;
            dfs(E[u][i], end);
        }
    }
}
int main() {
    memset(vis, 0, sizeof(vis));
    int i, u, v;
    cin >> N >> M;
    for (i = 1; i <= M; i++) {
        cin >> u;
        cin >> v;
        E[v].push_back(u);
    }
    for (i = N; i >= 1; i--) {
        if (!vis[i]) {
            vis[i] = i;
            dfs(i, i);
        }
    }
    for (i = 1; i <= N; i++) {
        cout << vis[i] << ' ';
    }
}
