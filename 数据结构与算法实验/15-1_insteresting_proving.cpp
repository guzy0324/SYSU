/*
做法：以R(s1, s2): s1 + s2 < s2 + s1排序（考虑了前缀问题
证明：
排序：将序列以s1 R s2 R ... R sn的顺序输出
所以证明就需要先证明R具有传递性证明排序可行，再来证明排序做法的正确性

传递性：要证a + b < b + a, b + c < c + b => a + c < c + a，不妨去找a + b < b + a的等价条件
a + b < b + a <=> 存在i使(a + b)[0, i - 1] == (b + a)[0, i - 1], (a + b)[i] < (b + a)[i]
                  1. i < len(a), i < len(b)  <=> a < b
                  2. i < len(a), i >= len(b) <=> 设a = b + c, b + c + b < b + b + c <=> c + b < b + c
                  3. i >= len(a), i < len(b) <=> 设b = a + c, a + a + c < a + c + a <=> a + c < c + a
由上可知，1为递归终点，2，3递归调用。（因为a和b长度一定，且若一直是2，3情况则a + b == b + a。所以一定可以达到递归终点
 <=> 存在k10, k20使k1 >= k10, k2 >= k20时k1 * a  < k2 * b
通过这个等价条件易证传递性

正确性：
      因为排序后序列s1, s2, ...，中si < s(i + 1)
      所以不存在中si和si + 1交换位置使（i < j）... + si + si + 1 + ... > ... + sj + si + 1 + ...
      然后其他情况都可以通过相邻交换获得
*/
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
#define MAX_NUM 101
int n;
string s[MAX_NUM];
bool cmp (const string& s1, const string& s2) {
    return s1 + s2 < s2 + s1;
}
int main() {
    int i;
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> s[i];
    }
    sort(s, s + n, cmp);
    for (i = n - 1; i >= 0; i--) {
        cout << s[i];
    }
}
