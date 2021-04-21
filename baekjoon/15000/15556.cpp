#include <bits/stdc++.h>
using namespace std;

constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;

struct min_heap_elem {
    int64_t d;
    int u;
    min_heap_elem(int64_t d, int u) : d(d), u(u) {}
    bool operator<(const min_heap_elem& rhs) const {
        return d > rhs.d;
    }
};

struct max_heap_elem {
    int64_t d;
    int u;
    max_heap_elem(int64_t d, int u) : d(d), u(u) {}
    bool operator<(const max_heap_elem& rhs) const {
        return d < rhs.d;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, s, t, m1, m2;
    cin >> n >> m >> s >> t >> m1 >> m2;
    --s, --t, --m1, --m2;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    auto dijk = [&](int src) {
        vector<int64_t> dist(n, INF);

        priority_queue<min_heap_elem> pq;
        pq.emplace(dist[src] = 0, src);

        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (const auto& [w, v] : adj[u])
                if (dist[v] > d + w)
                    pq.emplace(dist[v] = d + w, v);
        }
        return dist;
    };

    auto dist = dijk(s);
    auto dist_from_u = dijk(m1), dist_from_v = dijk(m2);

    auto rev_ord = [&]() {
        vector<bool> visited(n);
        visited[t] = true;

        priority_queue<max_heap_elem> pq;
        pq.emplace(dist[t], t);

        vector<int> vtx;
        while (!pq.empty()) {
            const auto [d, v] = pq.top();
            pq.pop();

            vtx.emplace_back(v);
            auto it = remove_if(adj[v].begin(), adj[v].end(), [&](auto& edge) {
                auto& [w, u] = edge;
                if (d != dist[u] + w) {
                    return true;
                }
                if (!visited[u]) {
                    visited[u] = true;
                    pq.emplace(dist[u], u);
                }
                return false;
            });
            adj[v].erase(it, adj[v].end());
        }
        return vtx;
    }();

    assert(rev_ord.front() == t);
    assert(rev_ord.back() == s);
    assert(adj[s].empty());

    auto solve = [&](const vector<int64_t>& dp1, vector<int64_t>&& dp2) {
        for (const auto& v : rev_ord)
            for (const auto& [w, u] : adj[v])
                dp2[u] = min(dp2[u], dp2[v]);

        int64_t ret = INT64_MAX;
        for (int i = 0; i < n; ++i)
            ret = min(ret, dp1[i] + dp2[i]);
        return ret;
    };

    cout << min(solve(dist_from_u, vector<int64_t>(dist_from_v)),
                solve(dist_from_v, vector<int64_t>(dist_from_u)));
}