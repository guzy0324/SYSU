#include<iostream>
#include<string>
using namespace std;
struct node {
    char val;
    node* left;
    node* right;
    node(char v):val(v), left(nullptr), right(nullptr){}; 
};
string a, b;
char c;
int i = 0;
void create(int lia, int ria, int lib, int rib) {
    cout << b[rib - 1];
    int ri1, ri2;
    for (ri1 = lia, ri2 = lib; a[ri1] != b[rib - 1]; ri1++, ri2++);
    if (ri2 > lib) {
        create(lia, ri1, lib, ri2);
    }
    if (rib - 1 > ri2) {
        create(ri1 + 1, ria, ri2, rib - 1);
    }
}
int main() {
    int la, lb;
    cin >> a >> b;
    create(0, a.length(), 0, b.length());
}
