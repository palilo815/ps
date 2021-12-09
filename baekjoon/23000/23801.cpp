#include <bits/stdc++.h>

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

template <typename key_t, typename value_t>
struct min_heap_elem {
    key_t key;
    value_t value;

    min_heap_elem() = default;
    min_heap_elem(const key_t& key, const value_t& value) : key(key), value(value) {}

    bool operator<(const min_heap_elem& rhs) const { return key > rhs.key; }
};

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    auto dijk = [&](const int s) {
        vector dist(n, INF);
        priority_queue<min_heap_elem<int64_t, int>> pq;
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
    int s, t;
    cin >> s >> t, --s, --t;
    auto d0 = dijk(s);
    auto d1 = dijk(t);
    int64_t ans = INF;
    cin >> m;
    for (int x; m--;) {
        cin >> x, --x;
        chmin(ans, d0[x] + d1[x]);
    }
    cout << (ans == INF ? -1 : ans);
}

