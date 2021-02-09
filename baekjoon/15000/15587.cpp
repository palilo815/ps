#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, root;
    cin >> n >> root, --root;

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> d1(n), d2(n, 0x3f3f3f3f);
    function<void(int, int)> dfs = [&](int u, int p) {
        bool leaf = true;
        for (auto& v : adj[u])
            if (v != p) {
                leaf = false;
                d1[v] = d1[u] + 1;
                dfs(v, u);
                d2[u] = min(d2[u], d2[v] + 1);
            }
        if (leaf) d2[u] = 0;
    };
    dfs(root, -1);

    function<int(int, int)> solve = [&](int u, int p) {
        if (d1[u] >= d2[u]) return 1;
        int ret = 0;
        for (auto& v : adj[u])
            if (v != p)
                ret += solve(v, u);
        return ret;
    };
    cout << solve(root, -1);
}