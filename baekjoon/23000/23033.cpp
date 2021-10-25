#include <bits/stdc++.h>
using namespace std;

template <typename key_t, typename value_t>
struct min_heap_elem {
    key_t key;
    value_t value;

    min_heap_elem() = default;
    min_heap_elem(const key_t& key, const value_t& value) : key(key), value(value) {}

    bool operator<(const min_heap_elem& rhs) const {
        return key > rhs.key;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    int n, m;
    cin >> n >> m;
    vector<vector<tuple<int, int, int>>> adj(n);
    for (int u, v, t, w; m--;) {
        cin >> u >> v >> t >> w, --u, --v;
        adj[u].emplace_back(t, w, v);
    }
    vector dist(n, INF);
    priority_queue<min_heap_elem<int, int>> pq;
    pq.emplace(dist[0] = 0, 0);
    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (const auto& [t, w, v] : adj[u]) {
            if (const auto dd = (d + w - 1) / w * w + t;
                dist[v] > dd) {
                pq.emplace(dist[v] = dd, v);
            }
        }
    }
    cout << dist.back();
}