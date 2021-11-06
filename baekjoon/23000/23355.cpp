#include <bits/stdc++.h>
using namespace std;

class heavy_light {
public:
    vector<vector<int>> adj;
    vector<int> par, sz, top, in;

    heavy_light(size_t n) : adj(n), par(n), sz(n), top(n), in(n) {
        for (int i = n - 1, u, v; i--;) {
            cin >> u >> v, --u, --v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        dfs(0);
        hld(0);
    }

    bool on_path(size_t u, size_t v, size_t k, bool include_lca) const {
        const auto target = in[k];
        bool found = false;
        for (; top[u] != top[v]; u = par[top[u]]) {
            if (sz[top[u]] > sz[top[v]]) swap(u, v);
            if (in[top[u]] <= target && target < in[u] + 1) found = true;
        }
        if (in[u] > in[v]) swap(u, v);
        if (in[u] <= target && target < in[v] + 1) found = true;
        return found && (include_lca || u != k);
    }

private:
    int dfs_time = 0;

    void dfs(size_t u) {
        sz[u] = 1;
        for (auto& v : adj[u]) {
            par[v] = u;
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            dfs(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }
    void hld(size_t u) {
        in[u] = dfs_time++;
        bool heavy = true;
        for (const auto& v : adj[u]) {
            top[v] = heavy ? top[u] : v;
            hld(v);
            heavy = false;
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    heavy_light hld(n);
    cin >> n;
    for (int i, j, k, l; n--;) {
        char op;
        bool include_lca;
        cin >> op >> i >> j >> k, --i, --j, --k;
        if (op == '1') {
            include_lca = true;
            if (i == k || j == k) {
                cout << "NO\n";
                continue;
            }
        } else {
            include_lca = false;
            cin >> l, --l;
            if (hld.in[k] < hld.in[l]) k = l;
        }
        cout << (hld.on_path(i, j, k, include_lca) ? "NO\n" : "YES\n");
    }
}