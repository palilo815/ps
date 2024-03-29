#include <bits/stdc++.h>
using namespace std;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<tuple<int, int, int>>> adj(n);
    for (int u, v, t, k; m--;) {
        cin >> u >> v >> t >> k, --u, --v;
        adj[u].emplace_back(t, k, v);
        adj[v].emplace_back(t, k, u);
    }
    vector dist(n << 1, INT_MAX);
    priority_queue<elem> pq;
    pq.emplace(dist[0] = 0, 0);
    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (const auto& [t, k, v] : adj[u >> 1]) {
            if (u & 1) {
                if (dist[v << 1 | 1] > dist[u] + t) {
                    pq.emplace(dist[v << 1 | 1] = dist[u] + t, v << 1 | 1);
                }
            } else {
                if (dist[v << 1] > dist[u] + t) {
                    pq.emplace(dist[v << 1] = dist[u] + t, v << 1);
                }
                if (dist[v << 1 | 1] > dist[u] + t - k) {
                    pq.emplace(dist[v << 1 | 1] = dist[u] + t - k, v << 1 | 1);
                }
            }
        }
    }
    for (int i = 3; i < n << 1; i += 2) {
        cout << dist[i] << '\n';
    }
}