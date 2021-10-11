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
    constexpr int mod = 1e9 + 9;
    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;
    int n, m, s, t;
    cin >> n >> m >> s >> t, --s, --t;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
    }
    vector dist(n, pair(INF, 0));
    vector<int> dp(n);
    priority_queue<min_heap_elem<pair<int64_t, int>, int>> pq;
    pq.emplace(dist[s] = {0, 0}, s);
    dp[s] = 1;
    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (const auto& [w, v] : adj[u]) {
            pair d2(d.first + w, d.second + 1);
            if (d2 < dist[v]) {
                pq.emplace(dist[v] = d2, v);
                dp[v] = dp[u];
            } else if (d2 == dist[v]) {
                dp[v] += dp[u];
                dp[v] %= mod;
            }
        }
    }
    if (dist[t].first == INF) return cout << -1, 0;
    cout << dist[t].first << '\n'
         << dist[t].second << '\n'
         << dp[t];
}