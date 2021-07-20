#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define MAX_NUM 101
int k, m, n, a[MAX_NUM], b[MAX_NUM], vis[MAX_NUM][MAX_NUM];
struct str {
    int x;
    int y;
    bool operator<(const str& st) const {
        if(a[x] + b[y] == a[st.x] + b[st.y]) {
            return y > st.y;
        }
        return a[x] + b[y] > a[st.x] + b[st.y];
    }
}* p;
priority_queue<str> q;
int main() {
    int i;
    cin >> k >> m >> n;
    for (i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (i = 0; i < n; i++) {
        cin >> b[i];
    }
    p = new str;
    p->x = 0;
    p->y = 0;
    q.push(*p);
    memset(vis, 0, sizeof(vis));
    vis[0][0] = 1;
    for (; k && !q.empty(); k--) {
        cout << a[q.top().x] << ',' << b[q.top().y] << ' ';
        if (q.top().y + 1 < n && !vis[q.top().x][q.top().y + 1]) {
            p = new str;
            p->x = q.top().x;
            p->y = q.top().y + 1;
            vis[q.top().x][q.top().y + 1] = 1;
            q.push(*p);
        }
        if (q.top().x + 1 < m && !vis[q.top().x + 1][q.top().y]) {
            p = new str;
            p->x = q.top().x + 1;
            p->y = q.top().y;
            vis[q.top().x + 1][q.top().y] = 1;
            q.push(*p);
        }
        q.pop();
    }
}
