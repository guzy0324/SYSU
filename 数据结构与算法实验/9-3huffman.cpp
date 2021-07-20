#include<iostream>
#include<queue>
using namespace std;
struct node {
	char c;
	int f;
	bool operator<(const node& v) const;
	node* l;
	node* r;
	node(char c = 'Z' + 1, int f = 0, node * l = nullptr, node * r = nullptr) : c(c), f(f), l(l), r(r) {};
};
bool node::operator<(const node& v) const {
	if (f == v.f) {
		return c > v.c;
	}
	return f > v.f;
}
void visit(node* T) {
	if (T == nullptr) {
		return;
	}
	visit(T->l);
	visit(T->r);
	if (T->c != 'Z' + 1) {
		cout << T->c << endl;
	}
}
priority_queue<node> q;
int k;
int main() {
	int i;
	cin >> k;
	char c;
	int f;
	for (i = 1; i <= k; i++) {
		cin >> c;
		cin >> f;
		node n(c, f);
		q.push(n);
	}
	while (q.size() != 1) {
		node* a = new node(q.top().c, q.top().f, q.top().l, q.top().r);
		q.pop();
		node* b = new node(q.top().c, q.top().f, q.top().l, q.top().r);
		q.pop();
		node c('Z' + 1, a->f + b->f, b, a);
		q.push(c);
	}
	node* n = new node(q.top().c, q.top().f, q.top().l, q.top().r);
    q.pop();
	visit(n);
}
