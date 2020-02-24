#include <bits/stdc++.h>
using namespace std;

const int max_V = 10000;

int cnt;
vector<int> adj[max_V + 1];
stack<int> stk;
bool in_stack[max_V + 1];
int disc[max_V + 1], low[max_V + 1];

vector<vector<int>> ans;

void DFS(int u) {
    disc[u] = low[u] = ++cnt;
    stk.push(u);
    in_stack[u] = true;
    for (int v : adj[u]) {
        if (!disc[v]) {
            DFS(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v])
            low[u] = min(low[u], disc[v]);
    }
    if (disc[u] == low[u]) {
        vector<int> tmp;
        while (1) {
            int x = stk.top(); stk.pop();
            tmp.emplace_back(x);
            in_stack[x] = false;
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
    while(E--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }
    for (int i = 1; i <= V; ++i) if (!disc[i])
        DFS(i);
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