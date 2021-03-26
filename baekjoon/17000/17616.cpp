#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, x;
    cin >> n >> m >> x, --x;

    vector<vector<int>> adj(n), rev(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    }

    vector<int> stk;
    vector<bool> visited(n);
    auto dfs = [&](vector<vector<int>>& g) {
        fill(visited.begin(), visited.end(), false);
        int cnt = -1;
        for (stk.emplace_back(x); !stk.empty();) {
            const auto u = stk.back();
            stk.pop_back();
            ++cnt;
            for (const auto& v : g[u])
                if (!visited[v]) {
                    visited[v] = true;
                    stk.emplace_back(v);
                }
        }
        return cnt;
    };
    cout << dfs(rev) + 1 << ' ' << n - dfs(adj) << '\n';
}