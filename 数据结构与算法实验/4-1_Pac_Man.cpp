#include<stdio.h>
#include<vector>
#include<stack>
using namespace std;
int n;
int main () {
    scanf("%d", &n);
    stack<pair<int, int>> s;
    int a, b;
    while(scanf("%d %d", &a, &b) != EOF) {
        while (1) {
            if (b || s.empty() || !s.top().second) {
                s.push({a, b});
                break;
            }
            else if (s.top().first < a) {
                s.pop();
            }
            else {
                break;
            }
        }
    }
    printf("%d", s.size());
}
