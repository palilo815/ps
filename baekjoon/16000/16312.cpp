#include <bits/stdc++.h>
using namespace std;

constexpr int mxS = 10;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, s;
    cin >> n >> m >> s;

    vector<int> p(n);
    for (auto& x : p) cin >> x;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    vector<pair<int, int>> shelter(s);
    for (auto& [loc, capa] : shelter)
        cin >> loc >> capa, --loc;

    vector<array<int64_t, mxS>> dist(n);
    memset(dist.data(), 0x3f, sizeof(dist[0]) * dist.size());

    auto dijk = [&](const int i) {
        struct elem {
            int64_t d;
            int u;
            elem(int64_t d, int u) : d(d), u(u) {}
            bool operator<(const elem& rhs) const {
                return d > rhs.d;
            }
        };

        priority_queue<elem> pq;
        pq.emplace(dist[shelter[i].first][i] = 0, shelter[i].first);

        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u][i]) continue;

            for (const auto& [w, v] : adj[u])
                if (dist[v][i] > d + w)
                    pq.emplace(dist[v][i] = d + w, v);
        }
    };
    for (int i = 0; i < s; ++i)
        dijk(i);

    vector<int64_t> exceed(1 << s);
    auto valid = [&](const int64_t d) {
        fill(exceed.begin(), exceed.end(), 0);

        for (int u = 0; u < n; ++u) {
            int mask = 0;
            for (int i = 0; i < s; ++i)
                if (dist[u][i] <= d)
                    mask |= 1 << i;
            exceed[mask] += p[u];
        }
        if (exceed[0]) return false;

        for (int i = 0; i < s; ++i)
            exceed[1 << i] -= shelter[i].second;

        for (int i = 0; i < s; ++i)
            for (int mask = 0; mask < 1 << s; ++mask)
                if (mask >> i & 1)
                    exceed[mask] += exceed[mask ^ 1 << i];

        return all_of(exceed.begin(), exceed.end(), [&](auto& x) {
            return x <= 0;
        });
    };

    int64_t lo = 0, hi = 1e14;
    while (lo != hi) {
        const auto mid = lo + hi >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}