#include <bits/stdc++.h>
using namespace std;

const int max_V = 10000;

int t;
vector<int> adj[max_V + 1];
stack<int> stk;
bool on_stack[max_V + 1];
int disc[max_V + 1], low[max_V + 1];

vector<vector<int>> ans;

void dfs(int u) {
    disc[u] = low[u] = ++t;
    on_stack[u] = true;
    stk.emplace(u);

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        vector<int> tmp;
        while (1) {
            int x = stk.top(); stk.pop();
            tmp.emplace_back(x);
            on_stack[x] = false;
            if (x == u) break;
        }
        ans.emplace_back(tmp);
    }
}
bool cmp(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }
    for (int i = 1; i <= V; ++i)
        if (!disc[i])
            dfs(i);
    for (vector<int>& v : ans)
        sort(v.begin(), v.end());
    sort(ans.begin(), ans.end(), cmp);

    cout << ans.size();
    for (vector<int>& v : ans) {
        cout << '\n';
        for (int x : v) cout << x << ' ';
        cout << -1;
    }
    return 0;
}