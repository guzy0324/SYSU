#include<iostream>
#include<algorithm>
using namespace std;
#define SIZE 1000001
int n, v[SIZE], l[SIZE], r[SIZE], M = 1;
int cmp(int T1, int T2) {
    if (T1 == -1 && T2 == -1) {
        return 0;
    }
    else if ((T1 == -1 || T2 == -1) || v[T1] != v[T2]) {
        return -1;
    }
    else {
        int n1 = cmp(l[T1], r[T2]);
        int n2 = cmp(r[T1], l[T2]);
        if (n1 == -1 || n2 == -1) {
            return -1;
        }
        else {
            return n1 + n2 + 2;
        }
    }
}
int main() {
    int i;
    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    for (i = 1; i <= n; i++) {
        M = max(M, cmp(r[i], l[i]) + 1);
    }
    cout << M;
}
