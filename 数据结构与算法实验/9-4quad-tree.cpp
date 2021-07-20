#include<iostream>
#include<queue>
using namespace std;
int k;
struct node {
	float x;
	float y;
	node* top_left;
	node* top_right;
	node* bottom_left;
	node* bottom_right;
	node(float x, float y) : x(x), y(y), top_left(nullptr), top_right(nullptr), bottom_left(nullptr), bottom_right(nullptr) {};
	node(node* n) : x(n->x), y(n->y), top_left(nullptr), top_right(nullptr), bottom_left(nullptr), bottom_right(nullptr) {};
}*T = nullptr;
bool is_leaf(node* root) {
	return root->top_left == nullptr && root->top_right == nullptr && root->bottom_left == nullptr && root->bottom_right == nullptr;
}
void insert(node* n, node* (&root) = T, float l = 0, float r = 10, float b = 0, float t = 10) {
	if (root == nullptr) {
		root = n;
	}
	else {
		float x_mid = (l + r) / 2;
		float y_mid = (b + t) / 2;
		if (is_leaf(root)) {
			node* n0 = new node(root);
			if (root->x <= x_mid) {
				if (root->y <= y_mid) {
					insert(n0, root->bottom_left, l, x_mid, b, y_mid);
				}
				else {
					insert(n0, root->top_left, l, x_mid, y_mid, t);
				}
			}
			else {
				if (root->y <= y_mid) {
					insert(n0, root->bottom_right, x_mid, r, b, y_mid);
				}
				else {
					insert(n0, root->top_right, x_mid, r, y_mid, t);
				}
			}
		}
		if (n->x <= x_mid) {
			if (n->y <= y_mid) {
				insert(n, root->bottom_left, l, x_mid, b, y_mid);
			}
			else {
				insert(n, root->top_left, l, x_mid, y_mid, t);
			}
		}
		else {
			if (n->y <= y_mid) {
				insert(n, root->bottom_right, x_mid, r, b, y_mid);
			}
			else {
				insert(n, root->top_right, x_mid, r, y_mid, t);
			}
		}
	}
}
int main() {
	cin >> k;
	int i;
	for (i = 1; i <= k; i++) {
		float x, y;
		cin >> x >> y;
		node* n = new node(x, y);
		insert(n);
	}
	queue<node*> q;
	q.push(T);
	while (!q.empty()) {
		if (q.front() != nullptr) {
			if (is_leaf(q.front())) {
				cout << q.front()->x << ' ' << q.front()->y << endl;
			}
			q.push(q.front()->top_left);
			q.push(q.front()->top_right);
			q.push(q.front()->bottom_left);
			q.push(q.front()->bottom_right);
		}
		q.pop();
	}
}
