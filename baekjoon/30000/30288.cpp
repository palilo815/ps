#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector adj(n, vector<int>());
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector check(n, vector(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < static_cast<int>(adj[i].size()); ++j) {
            for (int k = 0; k < j; ++k) {
                const auto u = adj[i][j];
                const auto v = adj[i][k];
                if (check[u][v] != -1) {
                    cout << "TAIP\n";
                    cout << i + 1 << ' ' << u + 1 << ' ' << check[u][v] + 1 << ' ' << v + 1;
                    return 0;
                }
                check[u][v] = check[v][u] = i;
            }
        }
    }
    cout << "NE";
}
