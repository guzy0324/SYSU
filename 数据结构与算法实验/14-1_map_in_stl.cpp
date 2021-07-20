#include<iostream>
#include<string>
#include<map>
using namespace std;
string s;
int main() {
    cin >> s;
    map<string,int> mp;
    if (s.length() < 10) {
        return 0;
    }
    for(int i = 0; i <= s.length() - 10; i++) {
        string temp = s.substr(i,10);
        if (mp.find(temp) != mp.end()) {
            mp[temp]++;
        }
        else {
            mp[temp] = 0;
        }
    }
    for(map<string,int>::iterator it = mp.begin(); it!=mp.end(); it++) {
        if (it->second > 0) {
            cout << it->first << endl;
        }
    }
}
