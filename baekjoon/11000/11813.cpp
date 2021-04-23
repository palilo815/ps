#include <bits/stdc++.h>
using namespace std;

struct disjoint_set {
    vector<int> par;
    vector<map<int, int>> tree;
    disjoint_set(const vector<int>& dp) : par(dp.size(), -1), tree(dp.size()) {
        for (int i = 0; i < int(dp.size()); ++i)
            tree[i][dp[i]] = 1;
    }

    int find(int u) {
        return par[u] == -1 ? u : par[u] = find(par[u]);
    }
    int64_t merge(int u, int v) {
        u = find(u), v = find(v);
        if (tree[u].size() < tree[v].size())
            swap(u, v);

        int64_t ret = 0;
        for (const auto& [dp_val, cnt] : tree[v]) {
            ret += int64_t(cnt) * tree[u][dp_val];
            tree[u][dp_val] += cnt;
        }
        tree[v].clear();
        par[v] = u;
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n);
    vector<pair<int, int>> e(n - 1);
    for (auto& [u, v] : e) {
        int w;
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    // dp[i] = xorsum from root(0) to i
    // xorsum from u to v = dp[u] ^ dp[v]
    auto dp = [&](int src) {
        vector<int> stk = {src}, dp(n, -1);
        dp[src] = 0;

        while (!stk.empty()) {
            const auto u = stk.back();
            stk.pop_back();

            for (const auto& [w, v] : adj[u])
                if (dp[v] == -1) {
                    dp[v] = dp[u] ^ w;
                    stk.emplace_back(v);
                }
        }
        return dp;
    }(0);

    disjoint_set dsu(dp);

    vector<int> eid(n - 1);
    for (auto& x : eid) cin >> x, --x;

    vector<int64_t> ans(n);
    for (int i = n - 1; i--;)
        ans[i] = ans[i + 1] + dsu.merge(e[eid[i]].first, e[eid[i]].second);

    for (const auto& x : ans)
        cout << x << '\n';
}