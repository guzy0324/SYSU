#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int n, m;
int main() {
    scanf("%d %d", &n, &m);
    queue<int> q1, q2;
    vector<short> s;
    queue<int> bucket[10];
    int t = 1, len = 0;
    while (n--) {
        printf("%d", t);
        q1.push(2 * t + 1);
        q2.push(4 * t + 5);
        for (; t; t /= 10) {
            s.push_back(t % 10);
        }
        for (; !s.empty(); s.pop_back()) {
            bucket[s.back()].push(len++);
        }
        if (q1.front() < q2.front()) {
            t = q1.front();
            q1.pop();
        }
        else {
            t = q2.front();
            q2.pop();
        }
    }
    putchar('\n');
    int i;
    for (i = 0; i < len - m; i++) {
        for (t = 9; t >= 0; t--) {
            for (; !bucket[t].empty() && bucket[t].front() <= n; bucket[t].pop());
            if (!bucket[t].empty() && bucket[t].front() <= m + i) {
                putchar(t + '0');
                n = bucket[t].front();
                break;
            }
        }
    }
}
