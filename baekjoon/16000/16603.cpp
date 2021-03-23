#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> par(n), sz(n);
    par[0] = -1;

    auto dfs = [&](auto&& self, int u) -> void {
        sz[u] = 1;
        for (const auto& v : adj[u])
            if (v != par[u]) {
                par[v] = u;
                self(self, v);
                sz[u] += sz[v];
            }
    };
    dfs(dfs, 0);

    vector<pair<double, double>> ans(n);
    auto solve = [&](auto&& self, int u, double s, double e, double x, double y) -> void {
        ans[u] = {x, y};
        if (sz[u] == 1) return;
        double unit = (e - s) / (sz[u] - 1);
        for (const auto& v : adj[u]) {
            if (v == par[u]) continue;
            e = s + unit * sz[v];
            double X = x + cos((s + e) / 2.0);
            double Y = y + sin((s + e) / 2.0);
            self(self, v, s, e, X, Y);
            s = e;
        }
    };

    solve(solve, 0, 0, acos(-1) * 2.0, 0, 0);
    cout << fixed << setprecision(9);
    for (const auto& [x, y] : ans)
        cout << x << ' ' << y << '\n';
}