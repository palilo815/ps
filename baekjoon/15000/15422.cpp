#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct elem {
    int64_t d;
    int u;
    elem(int64_t d, int u) : d(d), u(u) {}
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
    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;
    int n, m, f, s, t;
    cin >> n >> m >> f >> s >> t;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    auto dijk = [&](int s) {
        vector dist(n, INF);
        priority_queue<elem> pq;
        pq.emplace(dist[s] = 0, s);
        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) {
                continue;
            }
            for (const auto& [w, v] : adj[u]) {
                if (dist[v] > d + w) {
                    pq.emplace(dist[v] = d + w, v);
                }
            }
        }
        return dist;
    };
    const auto d0 = dijk(s), d1 = dijk(t);
    assert(d0[t] == d1[s]);
    auto ans = d0[t];
    for (int u, v; f--;) {
        cin >> u >> v;
        chmin(ans, d0[u] + d1[v]);
    }
    cout << ans;
}