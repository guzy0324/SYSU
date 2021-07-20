#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAXN 100
int n, ve[MAXN], vl[MAXN];
struct e {
    int n;
    int w;
};
vector<int> path;
vector<e> v[MAXN], u[MAXN];
void get_critical_path() {
    int i, j, indegree[MAXN], total = 0;
    vector<int> st;
    for (i = 0; i < n; i++) {
        indegree[i] = u[i].size();
        if (!indegree[i]) {
            st.push_back(i);
        }
        ve[i] = 0;
    }
    while (!st.empty()) {
        j = st.back();
        st.pop_back();
        for (i = 0; i < v[j].size(); i++) {
            ve[v[j][i].n] = max(ve[v[j][i].n], ve[j] + v[j][i].w);
            total = max(total, ve[v[j][i].n]);
            indegree[v[j][i].n]--;
            if (!indegree[v[j][i].n]) {
                st.push_back(v[j][i].n);
            }
        }
    }
    for (i = 0; i < n; i++) {
        indegree[i] = v[i].size();
        if (!indegree[i]) {
            st.push_back(i);
        }
        vl[i] = total;
    }
    while (!st.empty()) {
        j = st.back();
        st.pop_back();
        for (i = 0; i < u[j].size(); i++) {
            vl[u[j][i].n] = min(vl[u[j][i].n], vl[j] - u[j][i].w);
            indegree[u[j][i].n]--;
            if (!indegree[u[j][i].n]) {
                st.push_back(u[j][i].n);
            }
        }
    }
    for (i = 0; i < n; i++) {
        indegree[i] = u[i].size();
        if (!indegree[i]) {
            st.push_back(i);
        }
    }
    while (!st.empty()) {
        j = st.back();
        if (ve[j] == vl[j]) {
            path.push_back(j);
        }
        st.pop_back();
        for (i = 0; i < v[j].size(); i++) {
            indegree[v[j][i].n]--;
            if (!indegree[v[j][i].n]) {
                st.push_back(v[j][i].n);
            }
        }
    }
}
int main() {
    cin >> n;
    int i, a, b, w;
    while (cin >> a >> b >> w) {
        v[a].push_back({b, w});
        u[b].push_back({a, w});
    }
    get_critical_path();
    cout << "ve" << endl;
    for (i = 0; i < n; i++) {
        cout << ve[i] << ' ';
    }
    cout << endl << "vl" << endl;
    for (i = 0; i < n; i++) {
        cout << vl[i] << ' ';
    }
    cout << endl << "path" << endl;
    for (i = 0; i < path.size(); i++) {
        cout << path[i] << ' ';
    }
}
