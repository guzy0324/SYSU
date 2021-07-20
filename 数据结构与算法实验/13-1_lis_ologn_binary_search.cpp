/*
最终l数组不是对应序列但是len一定是其长度，详见https://www.cnblogs.com/812-xiao-wen/p/10992613.html
*/
#include<iostream>
#include<algorithm>
using namespace std;
#define MAX_NUM 101
int n, a[MAX_NUM], l[MAX_NUM], len = 0;
int main() {
    cin >> n;
    int i, j;
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    l[len++] = a[0];
    for (i = 1; i < n; i++) {
        if (l[len - 1] < a[i]) {
            l[len++] = a[i];
        }
        else {
            *lower_bound(l, l + len, a[i]) = a[i];  //递增序列二分查找Ologn找[a[i], a[i]+d)不同于upperbound(a[i], a[i]+d]
        }                                           //递减序列要重载
    }
    cout << len;
}
