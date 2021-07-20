/*
类似背包
一维是树枝数量，一维是节点
for (j = min(sz[cur], q); j; j--) {
    for (k = 0; k <= min(j - 1, sz[e[cur][i].v]); k++) {
        dp[cur][j] = max(dp[cur][j], dp[cur][j - k - 1] + dp[e[cur][i].v][k] + e[cur][i].w);
    }
}
不同的是节点用树排序，需要用dfs来遍历，从叶子结点开始求解dp数组
存边双向存储，dfs通过增加一个参数pa来保证不会往回遍历
值得注意的是j从大到小遍历是因为每一次求解dp数组某点的数需要上一次dp数组该点前面的数
相当于先考虑一棵子树，再考虑另一棵子树，来获得两棵子树的最佳分配
*/
#include<stdio.h>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100
struct u {
    int v;
    int w;
};
int n, q, dp[MAXN + 1][MAXN], vis[MAXN + 1], sz[MAXN + 1];
vector<u> e[MAXN + 1];
void dfs(int cur, int pa) {
    sz[cur] = 1;
    int i, j, k;
    for (i = 0; i < e[cur].size(); i++) {
        if (e[cur][i].v != pa) {
            dfs(e[cur][i].v, cur);
            sz[cur] += sz[e[cur][i].v];
            for (j = min(sz[cur], q); j; j--) {
                for (k = 0; k <= min(j - 1, sz[e[cur][i].v]); k++) {
                    dp[cur][j] = max(dp[cur][j], dp[cur][j - k - 1] + dp[e[cur][i].v][k] + e[cur][i].w);
                }
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    scanf("%d", &q);
    int a, b, w;
    while (scanf("%d %d %d", &a, &b, &w) != EOF) {
        e[a].push_back({b, w});
        e[b].push_back({a, w});
    }
    memset(dp, 0, sizeof(dp));
    dfs(1, 0);
    printf("%d", dp[1][q]);
}
