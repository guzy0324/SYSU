#include <iostream>
using namespace std;
void quick_sort(int* a, int l, int r) {
    if (r <= l) {
        return;
    }
    int key = a[l], li = l, ri = r;
    while (li < ri) {
        while (li < ri && a[ri] <= key) {
            ri -= 1;
        }
        a[li] = a[ri];
        while (li < ri && a[li] >= key) {
            li += 1;
        }
        a[ri] = a[li];
    }
    a[li] = key;
    quick_sort(a, l, li - 1);
    quick_sort(a, li + 1, r);
}
int main() {
    int n, d, * a, i;
    cin >> n >> d;
    a = new int[n];
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    //quick_sort(a, 0, n - 1);
    int big_end = 0, num = 0;
    for (i = 0; big_end < n; big_end++) {
        while(i < n && a[big_end] - a[i] <= d) {
            i += 1;
        }
        if (i == n && a[big_end] - a[i] > d) {
            break;
        }
        num += (i - big_end - 1) * (i - big_end - 2) / 2;//等差数列求和
    }
    cout << num;
}
