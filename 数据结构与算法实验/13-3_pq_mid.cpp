#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define MAX_NUM 101
int n;
int main() {
    cin >> n;
    int mid, i, t;
    priority_queue<int, vector<int>, greater<int>> right;
    priority_queue<int, vector<int>, less<int>> left;
    cin >> mid;
    for (i = 1; i <= n; i += 2) {
        cout << mid << endl;
        cin >> t;
        if (t > mid) {
            right.push(t);
            left.push(mid);
        }
        else {
            left.push(t);
            right.push(mid);
        }
        cin >> t;
        if (t > mid) {
            right.push(t);
            mid = right.top();
            right.pop();
        }
        else {
            left.push(t);
            mid = left.top();
            left.pop();
        }
    }
}
