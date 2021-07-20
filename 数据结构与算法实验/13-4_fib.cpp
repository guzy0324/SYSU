/*
找规律
rabi: 1   2   3   45  678
fath: x   1   1   12  123
fib1: x   1   1   2   3
fib2: 1   1   2   3   5
*/
#include<iostream>
#include<vector>
using namespace std;
int a, b;
vector<int> fib({0, 1});
int main() {
    cin >> a >> b;
    if (a == b) {
        cout << a;
        return 0;
    }
    if (a > b) {
        a += b;
        b = a - b;
        a -= b;
    }
    while (fib.back() + *(fib.end() - 2) < b) {
        fib.push_back(fib.back() + *(fib.end() - 2));
    }
    while (1) {    
        b -= *(lower_bound(fib.begin(), fib.end(), b) - 1); //lower_bound和upper_bound都是找递增
        if (a == b) {                                       //但是lower_bound是找大于等于b的[b,b+d)
            cout << a;                                      //upper_bound是找大于b的(b,b+d]
            return 0;
        }
        if (a > b) {
            a += b;
            b = a - b;
            a -= b;
        }
    }
}
