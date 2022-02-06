#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    int s, t;
    cin >> s >> t, --s, --t;
    auto parametric = [&]<typename T>(T lo, T hi) {
        vector<uint_fast8_t> visited(n);
        vector<int> stk;
        auto f = [&](T mid) -> bool {
            auto ok = [&](const auto& edge) { return edge.first >= mid; };
            ranges::fill(visited, 0);
            visited[s] = 1;
            stk.emplace_back(s);
            while (!stk.empty()) {
                const auto u = stk.back();
                stk.pop_back();
                for (const auto& [w, v] : adj[u] | ranges::views::filter(ok)) {
                    if (!visited[v]) {
                        visited[v] = 1;
                        stk.emplace_back(v);
                    }
                }
            }
            return visited[t];
        };
        // // first true
        // while (lo != hi) {
        //     auto mid = lo + (hi - lo) / 2;
        //     f(mid) ? hi = mid : lo = mid + 1;
        // }
        // last true
        while (lo != hi) {
            auto mid = hi - (hi - lo) / 2;
            f(mid) ? lo = mid : hi = mid - 1;
        }
        return lo;
    };
    cout << parametric(1, int(1e9)) << '\n';
}
