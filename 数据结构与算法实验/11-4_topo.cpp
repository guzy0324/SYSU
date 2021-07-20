#include<iostream>
#include<vector>
using namespace std;
#define MAX_NUM 5001
int n, m, indegree[MAX_NUM], outdegree[MAX_NUM], dp[MAX_NUM];
vector<int> E[MAX_NUM];
int main() {
    cin >> n >> m;
    while(m--) {
        int A, B;
        cin >> A >> B;
        E[B].push_back(A);
        indegree[B]++;
        outdegree[A]++;
    }
    vector<int> s;
    for (int i = 1; i <= n; i++) {
        if (!outdegree[i]) {
            s.push_back(i);
            dp[i] = 1;
        }
    }
    while (!s.empty()) {
        int B = s.back();
        s.pop_back();
        for (int i = 0; i < E[B].size(); i++) {
            outdegree[E[B][i]]--;
            dp[E[B][i]] = (dp[E[B][i]] + dp[B]) % 80112002;
            if (!outdegree[E[B][i]]) {
                s.push_back(E[B][i]);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!indegree[i]) {
            ans = (ans + dp[i]) % 80112002;
        }
    }
    cout << ans;
}
