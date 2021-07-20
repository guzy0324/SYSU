/*
123 132 213 231 312 321
000 010 100 110 200 210
可考虑成从左到右第i位为i进制
下面是题解的优秀做法，防止数字过大导致超范围，所以就采用一个长度为n的数组来n位数，加m从尾部加然后分别计算进位。
还有更高级的优化做法详见https://www.luogu.com.cn/blog/abc123-yummy/huoxingren
*/
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
#define MAXN 10000
int n, m, vis[MAXN + 1], num[MAXN + 1];
int main() {
    cin >> n >> m;
    int i, j, coun;
    memset(vis, 0, sizeof(vis));
    for (i = 0; i < n; i++) {
        cin >> num[i];
        for (j = 1, coun = num[i] - 1; j < num[i]; j++) {
            if (vis[j]) {
                coun--;
            }
        }
        vis[num[i]] = 1;
        num[i] = coun;
    }
    j = m;
    for (i = 1; i <= n; i++) {
        num[n - i] += j;
        j = num[n - i] / i;
        num[n - i] %= i;
    }
    for (i = 0; i < n; i++) {
        for (j = 1, coun = num[i]; !vis[j] || coun; j++) {
            if (vis[j]) {
                coun--;
            }
        }
        vis[j] = 0;
        cout << j << ' ';
    }
}
