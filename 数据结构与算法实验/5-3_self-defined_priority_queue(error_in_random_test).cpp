#include<iostream>
#include<vector>
using namespace std;
inline long long MAX_INDEX(vector<long long*> a, long long i1, long long i2) {
	if (i1 >= a.size()) {
		if (i2 >= a.size()) {
			return a.size();
		}
		else {
			return i2;
		}
	}
	else if (i2 >= a.size()) {
		return i1;
	}
	else {
		return a[i1][0] > a[i2][0] ? i1 : i2;
	}
}
class priorityQ {
	vector<long long*> queue;
public:
	priorityQ(vector<long long*> a, long long size);
	long long size();
	long long* operator[] (long long i);
	void push(long long* n);
	long long* pop();
};
priorityQ::priorityQ(vector<long long*> a, long long size) {
	vector<long long*>::iterator i;
	long long j;
	for (i = a.begin(), j = 0; j < size; i++, j++);
	queue.assign(a.begin(), i);
	long long index = (queue.size() - 2) / 2;
	long long child_index_1 = index * 2 + 1;
	long long child_index_2 = index * 2 + 2;
	while (index >= 0) {
		long long i_temp = index;
		long long c_i_1_temp = child_index_1;
		long long c_i_2_temp = child_index_2;
		long long max_index = MAX_INDEX(queue, c_i_1_temp, c_i_2_temp);
		while (max_index < a.size() && queue[i_temp][0] < queue[max_index][0]) {
			long long* temp = queue[i_temp];
			queue[i_temp] = queue[max_index];
			queue[max_index] = temp;
			i_temp = max_index;
			c_i_1_temp = i_temp * 2 + 1;
			c_i_2_temp = i_temp * 2 + 2;
			max_index = MAX_INDEX(queue, c_i_1_temp, c_i_2_temp);
		}
		index--;
		child_index_1 = index * 2 + 1;
		child_index_2 = index * 2 + 2;
	}
}
long long priorityQ::size() {
	return queue.size();
}
long long* priorityQ::operator[](long long i) {
	return queue[i];
}
void priorityQ::push(long long* n) {
	queue.push_back(n);
	long long index = queue.size() - 1;
	long long parent_index = (index - 1) / 2;
	while (index != 0 && queue[parent_index][0] < n[0]) {
		queue[index] = queue[parent_index];
		index = parent_index;
		parent_index = (index - 1) / 2;
	}
	queue[index] = n;
}
long long* priorityQ::pop() {
	long long* ans = queue[0];
	long long* temp = queue.back();
	queue.pop_back();
	long long index = 0;
	long long child_index_1 = index * 2 + 1;
	long long child_index_2 = index * 2 + 2;
	long long max_index = MAX_INDEX(queue, child_index_1, child_index_2);
	while (true) {
		if (max_index < queue.size() && queue[max_index][0] >= temp[0]) {
			queue[index] = queue[max_index];
			index = max_index;
			child_index_1 = index * 2 + 1;
			child_index_2 = index * 2 + 2;
			max_index = MAX_INDEX(queue, child_index_1, child_index_2);
		}
		else if (index < queue.size()) {
			queue[index] = temp;
			break;
		}
		else {
			break;
		}
	}
	return ans;
}
int main() {
	long long n, k, i, cpd = 0, cost = 0;
	cin >> n >> k;
	vector<long long*> c(n, nullptr);
	for (i = 0; i < n; i++) {
		c[i] = new long long[2];
		cin >> c[i][0];
		c[i][1] = i;
	}
	priorityQ q(c, k);
	for (i = k; i < n; i++) {
		q.push(c[i]);
		long long* f = q.pop();
		cost += (i - f[1]) * f[0];
	}
	for (i = n; i < n + k; i++) {
		long long* f = q.pop();
		cost += (i - f[1]) * f[0];
	}
	cout << cost;
}
