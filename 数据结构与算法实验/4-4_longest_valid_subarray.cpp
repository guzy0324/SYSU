#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
int main() {
    char c;
    int i, ans;
    vector<char> s1;
    vector<int> s2({-1});
    for (i = 0; (c = getchar()) != EOF; i++) {
        if (c == ')' && !s1.empty() && s1.back() == '(') {
            s1.pop_back();
            s2.pop_back();
        }
        else {
            s1.push_back(c);
            s2.push_back(i);
        }
    }
    for (ans = i - s2.back() - 1, i = 1; i < s2.size(); i++) {
        ans = max(ans, s2[i] - s2[i - 1] - 1);
    }
    printf("%d", ans);
}
