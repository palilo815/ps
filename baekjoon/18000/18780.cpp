#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int mxN = 1e5;

vector<p> adj[mxN];
int a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, C;
    cin >> N >> M >> C;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    for (int u, v, w; C--;) {
        cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
    }

    stack<int> tp;
    vector<bool> visited(N);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (auto& [v, w] : adj[u])
            if (!visited[v])
                dfs(v);
        tp.emplace(u);
    };

    for (int i = 0; i < N; ++i)
        if (!visited[i])
            dfs(i);

    while (!tp.empty()) {
        int& u = tp.top();
        tp.pop();
        for (auto& [v, w] : adj[u])
            a[v] = max(a[v], a[u] + w);
    }

    for (int i = 0; i < N; ++i)
        cout << a[i] << '\n';
    return 0;
}