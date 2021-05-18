#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;

struct order {
    int s, u, t;
};

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
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = m, u, v, d; i--;) {
        cin >> u >> v >> d, --u, --v;
        adj[u].emplace_back(d, v);
        adj[v].emplace_back(d, u);
    }

    int k;
    cin >> k;

    vector<order> a(k);
    for (auto& [s, u, t] : a)
        cin >> s >> u >> t, --u;

    vector<vector<int64_t>> dist(n, vector<int64_t>(n, INF));
    {
        priority_queue<elem> pq;
        auto dijk = [&](int s) {
            pq.emplace(dist[s][s] = 0, s);
            while (!pq.empty()) {
                const auto [d, u] = pq.top();
                pq.pop();

                if (d != dist[s][u]) continue;

                for (const auto& [w, v] : adj[u])
                    if (dist[s][v] > d + w)
                        pq.emplace(dist[s][v] = d + w, v);
            }
        };
        for (int s = 0; s < n; ++s)
            dijk(s);
    }

    // dp[i] = i개 배달을 완료하는 데 걸리는 최소 시간
    vector<int64_t> dp(k + 1);

    auto ok = [&](int64_t lim) -> bool {
        fill_n(dp.begin() + 1, k, INF);

        for (int i = 0; i < k; ++i) {
            int64_t start = max(dp[i] + (i ? dist[0][a[i - 1].u] : 0), int64_t(a[i].t));
            int64_t cost = dist[a[i].u][0];
            int64_t extra = a[i].s + lim - (start + cost);
            if (extra < 0) continue;

            chmin(dp[i + 1], start + cost);

            for (int j = i + 1; j < k; ++j) {
                extra -= max(0ll, a[j].t - start);
                if (extra < 0) break;

                chmax(start, int64_t(a[j].t));
                cost += dist[a[j - 1].u][a[j].u];
                chmin(extra, a[j].s + lim - (start + cost));

                if (extra < 0) break;
                chmin(dp[j + 1], start + cost);
            }
        }
        return dp[k] != INF;
    };

    int64_t lo = 0, hi = 1e14;
    while (lo != hi) {
        auto mid = (lo + hi) >> 1;
        ok(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}