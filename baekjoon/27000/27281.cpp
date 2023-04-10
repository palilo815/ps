#include <bits/stdc++.h>

struct HeapNode {
    int key, value;

    HeapNode() = default;
    HeapNode(const int& key, const int& value) : key(key), value(value) {}

    auto operator<(const HeapNode& rhs) const -> bool { return key > rhs.key; }
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<tuple<int, int, int>>> adj(n);
    for (auto _ = m; _--;) {
        int u, v, t, s;
        cin >> u >> v >> t >> s, --u, --v;
        adj[u].emplace_back(t, s, v);
        adj[v].emplace_back(t, s, u);
    }
    auto parametric = [&]<typename T>(T lo, T hi) {
        vector<int> dist(n);
        priority_queue<HeapNode> pq;
        auto f = [&](T mid) -> bool {
            fill(dist.begin() + 1, dist.end(), k + 1);
            pq.emplace(0, 0);
            while (!pq.empty()) {
                const auto [d, u] = pq.top();
                pq.pop();
                if (d != dist[u]) continue;
                for (const auto& [t, s, v] : adj[u]) {
                    const auto dd = int64_t(d) + t + (s > mid ? s - mid : 0);
                    if (dist[v] > dd) {
                        pq.emplace(dist[v] = dd, v);
                    }
                }
            }
            return dist.back() != k + 1;
        };
        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };
    const auto ans = parametric(0, 1'000'000'001);
    cout << (ans == 1'000'000'001 ? -1 : ans);
}
