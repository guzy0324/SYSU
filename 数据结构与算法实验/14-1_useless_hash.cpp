#include<iostream>
#include<stack>
#include<algorithm>
#include<string>
using namespace std;
string s;
long long Hash[1001];
int main() {
    cin >> s;
    int i, j, k;
    long long t;
    for (i = 0; i <= s.length() - 10; i++) {
        Hash[i] = 0;
        for (j = 0; j < 10; j++) {
            Hash[i] = Hash[i] * 26 + s[i + j] - 'A';
        }
    }
    sort(Hash, Hash + s.length() - 9);
    stack<char> st;
    for (i = 0; i < s.length() - 10; i++) {
        for (j = i + 1; Hash[j] == Hash[i]; j++);
        if (i != j - 1) {
            for (k = 0, t = Hash[i]; k < 10; k++, t /= 26) {
                st.push(t % 26 + 'A');
            }
            for (; !st.empty(); cout << st.top(), st.pop());
            cout << endl;
            i = j - 1;
        }
    }    
}
