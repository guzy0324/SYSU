#include<iostream>
#include<queue>
using namespace std;
struct f {
	long long n;
	long long w;
	bool operator <(const f& ff) const {
		return w < ff.w;
	}
};
long long n, k;
int main() {
	scanf("%lld %lld", &n, &k);
	long long i = 0, ans = 0;
	priority_queue<f> pq;
	f t;
    for (; i < k; i++) {
        scanf("%lld", &t.w);
        t.n = i;
        pq.push(t);
    }
    for (; i < n; i++) {
        scanf("%lld", &t.w);
        t.n = i;
        pq.push(t);
        ans += (i - pq.top().n) * pq.top().w;
        pq.pop();
    }
    for (; i < n + k; i++) {
        ans += (i - pq.top().n) * pq.top().w;
        pq.pop();
    }
	printf("%lld", ans);
}
