#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int mxN = 1e4;

vector<p> adj[mxN];
int d1[mxN], d2[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, src, dst;
    cin >> N >> M;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
    }
    cin >> src >> dst;
    --src, --dst;

    vector<int> tp;
    vector<bool> visited(N);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (auto& [v, w] : adj[u])
            if (!visited[v])
                dfs(v);
        tp.emplace_back(u);
    };

    for (int i = 0; i < N; ++i)
        if (!visited[i])
            dfs(i);

    for (int& u : tp)
        for (auto& [v, w] : adj[u])
            d2[u] = max(d2[u], d2[v] + w);

    for (auto it = tp.rbegin(); it != tp.rend(); ++it) {
        int& u = *it;
        for (auto& [v, w] : adj[u])
            d1[v] = max(d1[v], d1[u] + w);
    }

    int mx = d1[dst], cnt = 0;
    for (int u = 0; u < N; ++u)
        for (auto& [v, w] : adj[u])
            if (d1[u] + w + d2[v] == mx)
                ++cnt;

    cout << mx << '\n'
         << cnt;
    return 0;
}