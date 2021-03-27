#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct RMQ {
    RMQ(const vector<T>& a) : n(a.size()), dp(__lg(n) + 1) {
        dp[0] = a;
        for (int i = 1, k = 1; i < int(dp.size()); ++i, k <<= 1) {
            dp[i].resize(n - (k << 1) + 1);
            for (int j = 0; j + (k << 1) <= n; ++j)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j + k]);
        }
    }
    T query(int l, int r) {
        assert(0 <= l && r <= n);
        if (l == r) return 0;
        const int k = __lg(r - l);
        return max(dp[k][l], dp[k][r - (1 << k)]);
    }

private:
    const int n;
    vector<vector<T>> dp;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> in(n, -1), out(n);
    int t = 0;
    auto dfs = [&](auto&& self, int u) -> void {
        in[u] = t++;
        for (const auto& v : adj[u])
            if (in[v] == -1)
                self(self, v);
        out[u] = t;
    };
    dfs(dfs, 0);

    vector<int> a_dfn(n);
    for (int i = 0; i < n; ++i)
        a_dfn[in[i]] = a[i];

    RMQ solver(move(a_dfn));

    int ans = 0;
    for (int u = 0; u < n; ++u) {
        int earn = max(solver.query(0, in[u]), solver.query(out[u], n));
        for (const auto& v : adj[u])
            if (in[u] < in[v])
                earn += solver.query(in[v], out[v]);
        ans = max(ans, earn);
    }
    cout << ans;
}