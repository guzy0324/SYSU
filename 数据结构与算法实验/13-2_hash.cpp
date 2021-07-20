#include<iostream>
#include<unordered_map>
using namespace std;
#define MAX_NUM 101
int N, C, a[MAX_NUM], ans;
unordered_map<int, int> mp;
int main() {
    int i;
    cin >> N >> C;
    for (i = 0; i < N; i++, cin >> a[i], mp[a[i] + C]++);
    for (i = 0; i < N; i++, ans += mp[a[i]]);
    cout << ans;
}
