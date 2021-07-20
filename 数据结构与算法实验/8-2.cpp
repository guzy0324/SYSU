#include<iostream>
#include<string>
using namespace std;
string s1, s2;
int count(int root1, int end1, int root2, int end2) {
	if (root1 == end1 && root2 == end2) {
		return 1;
	}
	if (s1[root1 + 1] == s2[root2 - 1]) {
		return 2 * count(root1 + 1, end1, root2 - 1, end2);
	}
	int i, j, num;
	for (i = root2 - 2; s1[root1 + 1] != s2[i]; i--);
	for (j = root1 + 2; s1[j] != s2[root2 - 1]; j++);
	return count(root1 + 1, j - 1, i, end2) * count(j, end1, root2 - 1, i + 1);
}
int main() {
	cin >> s1;
	cin >> s2;
	cout << count(0, s1.length() - 1, s2.length() - 1, 0);
}
