/*
十分impressive的prooving：
1. 对于数组一般考虑sorted的
2. 此题马互不相同，不考虑ai == bj
3. 我们希望找到i和j的映射关系来通过ai > bj判断能否平局（找不到就只能暴力）
若n为奇数：不可能平局
若n为偶数：
对于sorted的数组a，b：ai > bj 
                    => {ai, ..., an} > {b1, ..., bj} 
                    => 至少有max(j - i + 1, 0)个a胜b
考虑j - i <= n / 2 - 1：ai > bj => 至少有m个a胜b（m <= n / 2）=> 无意义
考虑j - i >= n / 2：ai > bj => 至少有m个a胜b（m >= n / 2 + 1）=> 不可能平局
所以：存在ai > bj（j - i >= n / 2）来 => 不可能平局
因为：任意ai < bj && aj > bi（j - i == n / 2）=> 一定能平局
所以：n为奇数时：不可能平局
      n为偶数时：j - i == n / 2时判断是否存在ai > bj或aj < bi可以判断是否一定能平局
*/
#include<iostream>
#include<algorithm>
using namespace std;
#define MAX_NUM 100
int n, h1[MAX_NUM], h2[MAX_NUM];
int main() {
    cin >> n;
    if (n % 2) {
        cout << "NO";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> h1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> h2[i];
    }
    sort(h1, h1 + n);
    sort(h2, h2 + n);
    int flag = 1;
    for (int i = 0; i < n / 2; i++) {
        if (h1[i] > h2[n / 2 + i] || h1[n / 2 + i] < h2[i]) {
            flag = 0;
        };
    }
    if (flag) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
