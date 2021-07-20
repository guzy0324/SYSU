#include<iostream>
using namespace std;
int dir[][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1,-1}, {0, -1} }, max = 0, **vis, **a, N, M;
void dfs(int x, int y, int num) {
	extern int dir[][2], max, ** vis, ** a, N, M;
	int j, xt, yt;
	if (y == M - 1) {
		if (x == N - 1) {
			if (num > max) {
				max = num;
			}
			return;
		}
		else {
			xt = x + 1;
			yt = 0;
		}
	}
	else {
		xt = x;
		yt = y + 1;
	}
	for (j = 0; j < 8; j++) {
		if (0 <= xt + dir[j][0] && xt + dir[j][0] < N && 0 <= yt + dir[j][1] && yt + dir[j][1] < M && vis[xt + dir[j][0]][yt + dir[j][1]]) {
			break;
		}
	}
	if (j == 8) {
		vis[xt][yt] = 1;
		dfs(xt, yt, num + a[xt][yt]);
		vis[xt][yt] = 0;
	}
	dfs(xt, yt, num);
}
int main() {
	extern int N, M, ** a, ** vis, max;
	int i,j;
	cin >> N >> M;
	a = new int*[N], vis = new int*[N];
	for (i = 0; i < N; i++) {
		a[i] = new int[M];
		vis[i] = new int[M];
		for (j = 0; j < M; j++) {
			cin >> a[i][j];
			vis[i][j] = 0;
		}
	}
	dfs(0, 0, 0);
	vis[0][0] = 1;
	dfs(0, 0, a[0][0]);
	cout << max;
}
