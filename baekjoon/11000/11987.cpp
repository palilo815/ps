#include <bits/stdc++.h>
using namespace std;

struct elem {
    pair<int, int> d;
    int u;
    elem(pair<int, int> d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        if (d.first == rhs.d.first) return d.second < rhs.d.second;
        return d.first > rhs.d.first;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    int n, m, q;
    cin >> n >> m >> q;
    const auto adj = [&]() {
        vector<pair<int, int>> e(m);
        for (auto& [u, v] : e) {
            cin >> u >> v, --u, --v;
        }
        vector changed(m, INF);
        for (int i = 0, eid; i < q; ++i) {
            cin >> eid, --eid;
            changed[eid] = i;
        }
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < m; ++i) {
            adj[e[i].first].emplace_back(changed[i], e[i].second);
            adj[e[i].second].emplace_back(changed[i], e[i].first);
        }
        return adj;
    }();
    vector<pair<int, int>> dist(n, pair(INF, INF));
    priority_queue<elem> pq;
    pq.emplace(dist[0] = {0, INF}, 0);
    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (const auto& [t, v] : adj[u]) {
            const auto t2 = min(t, d.second);
            if (dist[v].first > d.first + 1 || (dist[v].first == d.first + 1 && dist[v].second < t2)) {
                pq.emplace(dist[v] = {d.first + 1, t2}, v);
            }
        }
    }
    vector<int> ans(q);
    for (const auto& [_, t] : dist) {
        if (t != INF) {
            ++ans[t];
        }
    }
    partial_sum(ans.begin(), ans.end(), ans.begin());
    for (const auto& x : ans) {
        cout << x << '\n';
    }
}