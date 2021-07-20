#include<iostream>
#include<string>
using namespace std;
int main() {
    string s, t("#");
    cin >> s;
    int* a = new int[s.length() * 2 + 1], i, id = 0, mx = 0, max_i = 0;
    for (i = 0; i < s.length(); i++) {
        t += s[i];
        t += "#";
    }
    for (i = 0; i < t.length(); i++) {
        if (mx > i) {
            a[i] = a[id - (i - id)];
        }
        else {
            a[i] = 0;
        }
        while (i + a[i] + 1 < t.length() && i - a[i] - 1 >= 0 && t[i + a[i] + 1] == t[i - a[i] - 1]) {
            a[i]++;
        }
        if (i + a[i] > mx) {
            id = i;
            mx = i + a[i];
        }
        if (a[i] > a[max_i]) {
            max_i = i;
        }
    }
    for (i = max_i - a[max_i]; i <= max_i + a[max_i]; i++) {
        if (t[i] != '#') {
            cout << t[i];
        }
    }
}
