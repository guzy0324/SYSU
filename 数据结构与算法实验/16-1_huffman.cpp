/*
1. p = &q.top()如果q.pop()，p的值（那个地址）可能会变成新的值，跟容器实现有关（该操作不合法，不要这么用因为&q.top()是容器内的地址
2. 容器存数据的时候调用了拷贝构造函数，所以用容器存的时候不要用栈内存（所以会出现上面的情况x
3. 容器貌似经常调用析构函数（但是pop不会改变top，front，back等等的内存（内容会变，细思极恐
*/
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
struct ch {
    char c;
    int num;
    ch* left;
    ch* right;
    ch(char cc, int n, ch* l = nullptr, ch* r = nullptr): c(cc), num(n), left(l), right(r) {}
    bool operator< (const ch& t) const {
        return num > t.num;
    }
};
priority_queue<ch> pq;
int main() {
    char c;
    int coun[26], i;
    memset(coun, 0, sizeof(coun));
    while (cin >> c) {
        coun[c - 'a']++;
    }
    for (i = 0; i < 26; i++) {
        if (coun[i]) { 
            ch t = ch(i + 'a', coun[i]);
            pq.push(t);
        }
    }
    while (pq.size() != 1) {
        ch t = pq.top();
        ch* p1 = new ch(t.c, t.num, t.left, t.right);
        pq.pop();
        t = pq.top();
        ch* p2 = new ch(t.c, t.num, t.left, t.right);
        pq.pop();
        t = ch('\0', p1->num + p2->num, p1, p2);
        pq.push(t);
    }
    queue<ch> q;
    queue<int> h;
    q.push(pq.top());
    pq.pop();
    h.push(0);
    int ans = 0;
    while(!q.empty()) {
        ch* t = &q.front();
        q.pop();
        int x = h.front();
        h.pop();
        if (t->c) {
            ans += x * t->num;
        }
        if (t->left) {
            q.push(*(t->left));
            h.push(x + 1);
        }
        if (t->right) {
            q.push(*(t->right));
            h.push(x + 1);
        }
    }
    cout << ans;
}
