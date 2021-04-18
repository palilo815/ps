#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 0x3f3f3f3f;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<vector<tuple<int, int, int>>> query(n);
    for (int i = 0, u, v, d; i < k; ++i) {
        cin >> u >> v >> d, --u, --v;
        query[u].emplace_back(v, d, i);
    }

    vector<pair<int, int>> dist(n);
    auto bfs = [&](int src) {
        fill(dist.begin(), dist.end(), make_pair(INF, INF));
        dist[src].first = 0;

        queue<int> q;
        q.emplace(src);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            const bool odd = u < 0;
            if (u < 0) u = ~u;

            for (const auto& v : adj[u])
                if (odd && dist[v].first == INF) {
                    dist[v].first = dist[u].second + 1;
                    q.emplace(v);
                } else if (!odd && dist[v].second == INF) {
                    dist[v].second = dist[u].first + 1;
                    q.emplace(~v);
                }
        }
    };

    vector<bool> ans(k);
    for (int i = 0; i < n; ++i) {
        if (query[i].empty()) continue;
        bfs(i);
        for (const auto& [v, d, id] : query[i])
            if (d & 1)
                ans[id] = dist[v].second <= d;
            else
                ans[id] = dist[v].first ? dist[v].first <= d : !adj[v].empty();
    }

    for (const auto x : ans)
        cout << (x ? "TAK\n" : "NIE\n");
}