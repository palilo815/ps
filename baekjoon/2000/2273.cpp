#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr size_t MX_N = 256;
    bool adj[MX_N][MX_N] {}, rev[MX_N][MX_N] {};
    int n, m;
    cin >> n >> m;
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        adj[u][v] = true;
        rev[v][u] = true;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                adj[i][j] |= adj[i][k] & adj[k][j];
                rev[i][j] |= rev[i][k] & rev[k][j];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (adj[i][i]) {
            return cout << -1, 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << count(rev[i], rev[i] + n, true) + 1 << ' ' << n - count(adj[i], adj[i] + n, true) << '\n';
    }
}