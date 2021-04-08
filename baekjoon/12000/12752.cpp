#include <bits/stdc++.h>
using namespace std;

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
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k, m;
    cin >> n >> k >> m;

    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;

    vector<vector<int64_t>> dp(1 << k, vector<int64_t>(n, INF));
    for (int i = k, x; i--;) {
        cin >> x, --x;
        dp[1 << i][x] = 0;
    }

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    priority_queue<elem> pq;
    auto dijk = [&](vector<int64_t>& dist) {
        for (int i = 0; i < n; ++i)
            if (dist[i] != INF)
                pq.emplace(dist[i], i);

        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (const auto& [w, v] : adj[u])
                if (dist[v] > d + w)
                    pq.emplace(dist[v] = d + w, v);
        }
    };

    for (int mask = 1; mask < (1 << k); ++mask) {
        for (int sub = mask; sub; sub = (sub - 1) & mask)
            for (int i = 0; i < n; ++i)
                dp[mask][i] = min(dp[mask][i], dp[sub][i] + dp[mask ^ sub][i]);
        dijk(dp[mask]);
    }
    cout << *min_element(dp[(1 << k) - 1].begin(), dp[(1 << k) - 1].end());
}