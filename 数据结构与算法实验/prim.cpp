#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 100
int n, E[MAXN][MAXN], ans = 0, path[MAXN][MAXN];
pair<int, int> dp[MAXN];
void prim() {
	int i, j, vis;
	for (vis = 1; vis != n; vis++) {
		for (j = 0; !dp[j].first; j++);
		for (i = j + 1; i < n; i++) {
			if (dp[i].first && dp[i].first < dp[j].first) {
				j = i;
			}
		}
		ans += dp[j].first;
		path[dp[j].second][j] = E[dp[j].second][j];
		path[j][dp[j].second] = E[j][dp[j].second];
		for (i = 0; i < n; i++) {
			if (dp[i].first && E[j][i] < dp[i].first) {
				dp[i].first = E[j][i];
				dp[i].second = j;
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
		}
		dp[i].first = E[0][i];
		dp[i].second = 0;
	}
	prim();
	cout << ans << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << path[i][j] << '\t';
		}
		cout << endl;
	}
}
