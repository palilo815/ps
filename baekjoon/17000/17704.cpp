#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, s;
    cin >> n >> m >> s, --s;
    vector<vector<int>> adj(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    ranges::for_each(adj, [&](auto& x) { ranges::sort(x); });
    vector dep(n, -1);
    dep[s] = 0;
    vector stk(n, pair(0, 0));
    stk[0] = {s, 0};
    for (int p = 1; p;) {
        const auto [u, i] = stk[--p];
        if (const auto it = find_if(adj[u].begin() + i, adj[u].end(), [&](const auto& v) { return dep[v] == -1; });
            it != adj[u].end()) {
            dep[*it] = dep[u] + 1;
            stk[p++] = {u, it - adj[u].begin() + 1};
            stk[p++] = {*it, 0};
        }
    }
    for (const auto& x : dep) {
        cout << x << '\n';
    }
}
