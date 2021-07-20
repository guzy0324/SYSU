#include<iostream>
#include<string>
using namespace std;
float string2float(string& s, int& index) {
	float num;
	int exponent = 0;
	num = s[index++] - '0';
	for (; s[index] >= '0' && s[index] <= '9'; index++) {
		num = num * 10 + s[index] - '0';
	}
	if (s[index] == '.') {
		index++;
		for (; s[index] >= '0' && s[index] <= '9'; index++) {
			exponent--;
			num = num * 10 + s[index] - '0';
		}
	}
	for (; exponent < 0; exponent++) {
		num *= 0.1;
	}
	return num;
}
float calculate(string& s, int& index, float ans = 0) {
	char op = s[index++];
	if (op == ')') {
		return ans;
	}
	else if (op == '(') {
		return calculate(s, index);
	}
	float num;
	if (s[index] == '(') {
		num = calculate(s, index);
	}
	else {
		num = string2float(s, index);
	}
	if (op == '+') {
		if (index >= s.length()) {
			return ans + num;
		}
		if (s[index] == '+' || s[index] == '-' || s[index] == ')') {
			return calculate(s, index, ans + num);
		}
		else {
			return calculate(s, index, ans + calculate(s, index, num));
		}
	}
	else if (op == '-') {
		if (index >= s.length()) {
			return ans - num;
		}
		if (s[index] == '+' || s[index] == '-' || s[index] == ')') {
			return calculate(s, index, ans - num);
		}
		else {
			return calculate(s, index, ans - calculate(s, index, num));
		}
	}
	else if (op == '*') {
		if (index >= s.length()) {
			return ans * num;
		}
		return calculate(s, index, ans * num);
	}
	else {
		if (index >= s.length()) {
			return ans / num;
		}
		return calculate(s, index, ans / num);
	}
}
int main() {
	string s;
	cin >> s;
	int index = 0;
	cout << calculate(s, index);
}
