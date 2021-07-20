#include<iostream>
using namespace std;
template <class t>
struct node {
    t v;
    node<t>* l;
    node<t>* r;
    bool ltag;
    bool rtag;
    node(t v, node* l = nullptr, node* r = nullptr, bool ltag = 0, bool rtag = 0): \
    v(v), l(l), r(r), ltag(ltag), rtag(rtag) {};
    void insert(t n);
    void preorder(node* (&last));
};
template <class t>
struct binary_tree {
    node<t>* T;
    node<t>* last;
    binary_tree(t v): T(new node<t>(v)) {};
    void insert(t n) {T->insert(n);}
    void preorder() {T->preorder(last);}
};
template <class t>
void node<t>::insert(t n) {
    if (n < v) {
        if (!l || ltag) {
            ltag = 0;
            l = new node<t>(n);
        }
        else {
            l->insert(n);
        }
    }
    else if (n > v) {
        if (!r || rtag) {
            rtag = 0;
            r = new node<t>(n);
        }
        else {
            r->insert(n);
        }
    }
}
template <class t>
node<t>* last = nullptr;
template <class t>
void node<t>::preorder(node* (&last)) {
    node<t>* temp = last;
    if (last && last->rtag && !last->r) {
        temp->r = this;
    }
    cout << v << ' ';
    last = this;
    if (!rtag && !r) {
        rtag = 1;
    }
    if (!ltag) {
        if (!l) {
            ltag = 1;
            l = temp;
        }  
        else {
            l->preorder(last);
        }
    }
    if (!rtag && r) {
        r->preorder(last);
    }
}
int main() {
    int n, i;
    char v;
    cin >> n;
    cin >> v;
    binary_tree<char> T(v);
    for (i = 2; i <= n; i++) {
        cin >> v;
        T.insert(v);
    }
    T.preorder();
    cout << endl;
    node<char>* p = T.T;
    cout << p->v << ' ';
    p = p->l;
    while (p) {
        cout << p->v << ' ';
        p = p->r;
    }
}
