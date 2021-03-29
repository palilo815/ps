#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> iron(m), coal(k);
    for (auto& x : iron) cin >> x, --x;
    for (auto& x : coal) cin >> x, --x;

    vector<vector<int>> adj(n), rev(n);
    for (int i = 0, c, v; i < n; ++i)
        for (cin >> c; c--;) {
            cin >> v, --v;
            adj[i].emplace_back(v);
            rev[v].emplace_back(i);
        }

    queue<int> q;
    vector<int> d_src(n, -1), d_iron(n, -1), d_coal(n, -1);
    auto bfs = [&](vector<vector<int>>& g, vector<int>& dist) {
        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& v : g[u])
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.emplace(v);
                }
        }
    };

    q.emplace(0);
    d_src[0] = 0;
    bfs(adj, d_src);

    for (auto& x : iron) {
        q.emplace(x);
        d_iron[x] = 0;
    }
    bfs(rev, d_iron);

    for (auto& x : coal) {
        q.emplace(x);
        d_coal[x] = 0;
    }
    bfs(rev, d_coal);

    int ans = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (d_src[i] == -1 || d_iron[i] == -1 || d_coal[i] == -1) continue;
        ans = min(ans, d_src[i] + d_iron[i] + d_coal[i]);
    }
    if (ans == INT_MAX)
        cout << "impossible";
    else
        cout << ans;
}