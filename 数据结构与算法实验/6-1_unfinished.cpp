#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
string s;
int main() {
	cin >> s;
	int i = 0, j = 0, vis[256], ans = 0;
	memset(vis, -1, sizeof(vis));
	vis[s[0]] = 0;
	while (j < s.length()) {
		ans = max(ans, j + 1 - i);
		if (vis[s[j + 1]] == -1) {
			vis[s[j + 1]] = j + 1;
		    j++;
		}
		else {
            vis[s[i]] = -1;
            i++;
		}
	}
	cout << ans;
}
