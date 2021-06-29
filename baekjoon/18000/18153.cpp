#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    queue<int> q;
    q.emplace(0);

    vector dist(n, -1);
    dist[0] = 0;

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto& v : adj[u])
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.emplace(v);
            }
    }

    cout << dist.back() - 1;
}