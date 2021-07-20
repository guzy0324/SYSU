/*
又是贪心。。。证明其实很容易，每次切割消耗能量为当前木板的长度，我们希望总耗能最少。
首先要明确一点是切木板的次数是一定的，一定是n-1次（由2个边获得2 * n个边，每次切获得2个边）。
不妨反向思考，如果把一块切成两块相当于把两块合成一块。
如果本次合成用了最小的两块，那么将会获得该次能获得的最小的块影响后面，导致每次合成都不会有比它小的方式。
*/
#include<iostream>
#include<queue>
using namespace std;
int main() {
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> q;
    while (n--) {
        int l;
        cin >> l;
        q.push(l);
    }
    int ans = 0;
    while (q.size() != 1) {
        int a = q.top(), b;
        q.pop(); 
        b = q.top();
        q.pop();
        ans += a + b;
        q.push(a + b);
    }
    cout << ans;
}
