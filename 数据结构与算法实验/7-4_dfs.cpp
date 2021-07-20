#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 1025
int n, m, cakes[N], mouths[N], ans = 0;
void dfs(int i = 0) {
	extern int n, m, cakes[N], mouths[N], ans;
	ans = max(i, ans);
	i++;
	int k;
	for (k = 1; k <= n; k++) {
		if (cakes[k] >= mouths[i]) {
			cakes[k] -= mouths[i];
			dfs(i);
			cakes[k] += mouths[i];
		}
	}
}
int main() {
	extern int n, m, cakes[N], mouths[N], ans;
	memset(cakes, 0, sizeof(cakes));
	memset(mouths, 0, sizeof(mouths));
	int i;
	cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> cakes[i];
	}
	cin >> m;
	for (i = 1; i <= m; i++) {
		cin >> mouths[i];
	}
	sort(mouths + 1, mouths + m + 1);
	dfs();
	cout << ans;
}
