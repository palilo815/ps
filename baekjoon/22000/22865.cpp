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
    int n, a, b, c, m;
    cin >> n >> a >> b >> c >> m, --a, --b, --c;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    priority_queue<min_heap_elem<int, int>> pq;
    auto dijk = [&](const int s) {
        vector dist(n, INF);
        pq.emplace(dist[s] = 0, s);
        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            for (const auto& [w, v] : adj[u]) {
                if (dist[v] > d + w) {
                    pq.emplace(dist[v] = d + w, v);
                }
            }
        }
        return dist;
    };
    auto ans = dijk(a);
    for (const auto s : {b, c}) {
        auto res = dijk(s);
        transform(ans.begin(), ans.end(), res.begin(), ans.begin(), [&](const auto& l, const auto& r) {
            return min(l, r);
        });
    }
    cout << max_element(ans.begin(), ans.end()) - ans.begin() + 1;
}