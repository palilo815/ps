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

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    vector<int> dist(n, -1);
    dist[root] = 0;
    int giga = adj[root].size() == 1 ? -1 : root;
    auto dfs = [&](int src) {
        vector<int> stk;
        for (stk.emplace_back(src); !stk.empty();) {
            const auto u = stk.back();
            stk.pop_back();

            for (const auto& [w, v] : adj[u])
                if (dist[v] == -1) {
                    dist[v] = dist[u] + w;
                    stk.emplace_back(v);
                    if (giga == -1 && adj[v].size() != 2)
                        giga = v;
                }
        }
    };
    dfs(root);

    cout << dist[giga] << ' ' << *max_element(dist.begin(), dist.end()) - dist[giga];
}