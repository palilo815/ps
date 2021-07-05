#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int u, v, i = n - 1; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto rev_dfn = [&](int root) {
        vector<int> stk = {root}, dfn(n);
        for (auto& u : dfn) {
            u = stk.back();
            stk.pop_back();
            for (const auto& v : adj[u]) {
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                stk.emplace_back(v);
            }
        }
        reverse(dfn.begin(), dfn.end());
        return dfn;
    }(0);
    vector<bool> police(n);
    for (const auto& u : rev_dfn) {
        police[u] = any_of(adj[u].begin(), adj[u].end(), [&](const auto& v) { return !police[v]; });
    }
    cout << count(police.begin(), police.end(), true);
}