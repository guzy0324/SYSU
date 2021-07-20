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
    node<t>* del(t n);
    void preorder(node* (&last));
};
template <class t>
struct binary_tree {
    node<t>* T;
    node<t>* last;
    binary_tree(t v): T(new node<t>(v)) {};
    void insert(t n) {T->insert(n);}
    void del(t n) {
        if (n == T->v && (!T->l || T->ltag) && (!T->r || T->rtag)) {
            delete T;
            T = nullptr;
        }
        else {
            T->del();
        }
    }
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
void* node<t>::del(t n) {
    node<t>* temp;
    if (n < v) {
        if (n == l->v) {
            if (l->l && !l->ltag && l->r && !l->rtag) { //被删除节点有左右两个子节点
                if (!l->r->l || l->r->ltag) {
                    l->v = l->r->v;
                    l->r->del(v);
                }
                else {
                    for (temp = l->r; temp->l->l && !temp->l->ltag; temp = temp->l); //在右子树儿子中找最小元素填充删除节点
                    v = temp->l->v;
                    temp->del(v); //再删除节点的右子树儿子中删除最小元素
                }
            }
            else { //被删除节点有一个或无子节点
                temp = l;
                if (!l->l || l->ltag) {//有右孩子或无子节点
                    l = l->r;
                }
                else {//有左孩子或无子节点
                    l = l->l;
                }
                delete temp;
            }
        }
        else {
            l->del(n);
        }
    }
    else if (n > v) {
        if (n == r->v) {
            if (r->l && !r->ltag && r->r && !r->rtag) { //被删除节点有左右两个子节点
                if (!r->r->l || r->r->ltag) {
                    r->v = r->r->v;
                    r->r->del(v);
                }
                else {
                    for (temp = r->r; temp->l->l && !temp->l->ltag; temp = temp->l); //在右子树儿子中找最小元素填充删除节点
                    v = temp->l->v;
                    temp->del(v); //再删除节点的右子树儿子中删除最小元素
                }
            }
            else { //被删除节点有一个或无子节点
                temp = r;
                if (!r->l || r->ltag) {//有右孩子或无子节点
                    r = r->r;
                }
                else {//有左孩子或无子节点
                    r = r->l;
                }
                delete temp;
            }
        }
        else {
            r->del(n);
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
    T.del(' ');
}
