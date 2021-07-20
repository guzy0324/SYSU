#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct node {
	int k;
	node* p;
	node* next;
	node(int K = 0, node * n = nullptr, node * P = nullptr) : k(K), p(P), next(n) {};
}*h = new node;
int m;
void insert(int n) {
	vector<node*> stack, stack1;
	node* ptr = h, * new_node = new node(n);
	for (; ptr->p; ptr = ptr->p) {
		if (ptr->k < m - 1) {
			stack.clear();
			stack1.clear();
		}
		stack.push_back(ptr);
		for (; ptr->next && ptr->next->k < n; ptr = ptr->next);
		if (ptr->next && ptr->next->k == n) {
			delete new_node;
			return;
		}
		if (ptr->k < m - 1) {
			stack.clear();
			stack1.clear();
		}
		stack1.push_back(ptr);
	}
	stack.push_back(ptr);
	for (ptr = stack.back(); ptr->next && ptr->next->k < n; ptr = ptr->next);
	if (ptr->next && ptr->next->k == n) {
		delete new_node;
		return;
	}
	stack1.push_back(ptr);
	while (!stack.empty()) {
		if (new_node) {
			new_node->next = stack1.back()->next;
			stack1.back()->next = new_node;
			new_node = nullptr;
			stack.back()->k++;
			if (stack.back()->k == m) {
				for (ptr = stack.back(); stack.back()->k > m / 2 + 1; ptr = ptr->next, stack.back()->k--);
				stack.back()->k = m - stack.back()->k;
				new_node = ptr->next;
				ptr->next = nullptr;
				new_node->p = new node(m - stack.back()->k - 1, new_node->next);
				new_node->next = nullptr;
				if (stack.back() == h) {
					h = new node(1, new_node, stack.back());
				}
			}
		}
		stack.pop_back();
		stack1.pop_back();
	}
}
int main() {
	int t, n, i;
	node* ptr;
	cin >> t >> n;
	m = 2 * t;
	queue<node*> q;
	for (i = 1; i <= n; i++) {
		insert(i);
		q.push(h);
		while (!q.empty()) {
			ptr = q.front();
			q.pop();
			if (ptr->p) q.push(ptr->p);
			for (ptr = ptr->next; ptr; ptr = ptr->next) {
				cout << ptr->k << ' ';
				if (ptr->p) q.push(ptr->p);
			}
			cout << endl;
		}
		cout << endl;
	}
	for (ptr = h; ptr; ptr = ptr->p) {
		cout << ptr->next->k << ' ';
	}
	cout << endl;
	for (ptr = h; ptr; ptr = ptr->p) {
		for (; ptr->next; ptr = ptr->next);
		cout << ptr->k << ' ';
	}
}
