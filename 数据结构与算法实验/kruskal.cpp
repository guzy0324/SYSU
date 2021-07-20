#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXN 100
int n, ans = 0, pre[MAXN];
struct e{
	int a;
	int b;
	int w;
	e(int aa = MAXN, int bb = MAXN, int ww = 0): a(aa), b(bb), w(ww) {}
	bool operator<(const e& e0) const {
		return w > e0.w;
	}
};
vector<e> E, path;
int find(int x) {
	int r, t;
	for (r = x; r != pre[r]; r = pre[r]);
	for (; x != r; t = pre[x], pre[x] = r, x = t);
	return r;
}
void kruskal() {
	priority_queue<e> pq(E.begin(), E.end());
	e t;
	int i, ra, rb;
	for (i = 0; i < n - 1; i++) {
		for (t = pq.top(), pq.pop(); (ra = find(t.a)) == (rb = find(t.b)); t = pq.top(), pq.pop());
		ans += t.w;
		path.push_back(t);
		pre[ra] = pre[rb];
	}
}
int main() {
	cin >> n;
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			int w;
			cin >> w;
			if (j > i) {
				E.push_back(e(i, j, w));
			}
		}
		pre[i] = i;
	}
	kruskal();
	cout << ans << endl;
	for (i = 0; i < n - 1; i++) {
		cout << path[i].a <<  ',' << path[i].b << ':' << path[i].w <<  endl;
	}
}
