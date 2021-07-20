#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int k;
struct node {
    node* l;
    node* r;
    int v;
    int lbf;
    int rbf;
    node(int v): v(v), l(nullptr), r(nullptr), lbf(0), rbf(0) {};
}* T = nullptr;
void balance (node* (&root)) {
    node* temp;
    if (root->lbf - root->rbf >= 2) {
        if (root->l->rbf - root->l->lbf >= 1) {
            temp = root->l;
            root->l = temp->r;
            temp->r = root->l->l;
            root->l->l = temp;
            temp->rbf = root->l->lbf;
            root->l->lbf = max(temp->lbf, temp->rbf) + 1;
        }
        temp = root;
        root = temp->l;
        temp->l = root->r;
        root->r = temp;
        temp->lbf = root->rbf;
        root->rbf = max(temp->lbf, temp->rbf) + 1;
    }
    else if (root->rbf - root->lbf >= 2) {
        if (root->r->lbf - root->r->rbf >= 1) {
            temp = root->r;
            root->r = temp->l;
            temp->l = root->r->r;
            root->r->r = temp;
            temp->lbf = root->r->rbf;
            root->r->rbf = max(temp->lbf, temp->rbf) + 1;
        }
        temp = root;
        root = temp->r;
        temp->r = root->l;
        root->l = temp;
        temp->rbf = root->lbf;
        root->lbf = max(temp->lbf, temp->rbf) + 1;
    }
}
void insert(int v, node* (&root) = T) {
    if (root == nullptr) {
        root = new node(v);
        return;
    }
    if (v < root->v) {
        insert(v, root->l);
        root->lbf = max(root->l->lbf, root->l->rbf) + 1;
    }
    else if (root->v < v) {
        insert(v, root->r);
        root->rbf = max(root->r->lbf, root->r->rbf) + 1;
    }
    balance(root);
}
int main() {
    int i, v;
    cin >> k;
    for (i = 1; i <= k; i++) {
        cin >> v;
        insert(v);
    }
    queue<node*> output;
    output.push(T);
    while (!output.empty()) {
        if (output.front() != nullptr) {
            cout << output.front()->v << ' ';
            output.push(output.front()->l);
            output.push(output.front()->r);
        }
        output.pop();
    }
}
