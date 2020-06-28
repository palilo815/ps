#include<bits/stdc++.h>
using namespace std;

const int max_V = 10001;

vector<int> adj[max_V];
int disc[max_V], low[max_V];
bool on_stack[max_V];
int t;
stack<int> stk;
vector<vector<int>> ans;

void dfs(int u) {
    disc[u] = low[u] = ++t;
    stk.emplace(u);
    on_stack[u] = true;

    for (int& v : adj[u]) {
        if (!disc[v]) dfs(v);
        if (on_stack[v]) low[u] = min(low[u], low[v]);
    }

    if (disc[u] == low[u]) {
        vector<int> tmp;
        while (1) {
            int x = stk.top(); stk.pop();
            on_stack[x] = false;
            tmp.emplace_back(x);
            if (x == u) break;
        }
        ans.emplace_back(tmp);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }

    for (int i = 1; i <= V; ++i)
        if (!disc[i])
            dfs(i);

    for (auto& v : ans) sort(v.begin(), v.end());
    sort(ans.begin(), ans.end(), [] (const auto & a, const auto & b) -> bool { return a[0] < b[0]; });

    cout << ans.size();
    for (auto& v : ans) {
        cout << '\n';
        for (int& x : v) cout << x << ' ';
        cout << -1;
    }
    return 0;
}