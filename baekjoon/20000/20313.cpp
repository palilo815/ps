#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;
const int mxM = 2e3;

struct elem {
    int64_t d;
    int u;
    elem(int64_t d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

vector<pair<int, int>> adj[mxN];
int t[mxM];
int64_t dist[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, src, dst, k;
    cin >> n >> m >> src >> dst;
    --src, --dst;

    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v >> t[i];
        --u, --v;
        adj[u].emplace_back(i, v);
        adj[v].emplace_back(i, u);
    }

    memset(dist, 0x3f, sizeof(int64_t) * n);
    dist[src] = 0;

    auto dijk = [&]() {
        priority_queue<elem> pq;
        for (int i = 0; i < n; ++i)
            pq.emplace(dist[i], i);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (auto& [i, v] : adj[u])
                if (dist[v] > dist[u] + t[i])
                    pq.emplace(dist[v] = dist[u] + t[i], v);
        }
    };

    for (dijk(), cin >> k; k--; dijk())
        for (int i = 0; i < m; ++i)
            cin >> t[i];
    cout << dist[dst];
}