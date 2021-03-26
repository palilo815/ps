#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
    }

    vector<int> stk;
    vector<bool> visited(n);
    auto dfs = [&](int src) {
        int ret = -1;
        fill(visited.begin(), visited.end(), false);
        for (stk.emplace_back(src); !stk.empty();) {
            const auto u = stk.back();
            stk.pop_back();
            ++ret;
            for (const auto& v : adj[u])
                if (!visited[v]) {
                    visited[v] = true;
                    stk.emplace_back(v);
                }
        }
        return ret;
    };

    int ans = n * (n - 1) >> 1;
    for (int i = 0; i < n; ++i)
        ans -= dfs(i);
    cout << ans;
}