#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> colour(n);
    for (auto& x : colour) {
        cin >> x, --x;
    }
    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for (int i = 0, u, v, c; i < q; ++i) {
        char op;
        cin >> op >> u, --u;
        if (op == 'U') {
            cin >> c, --c;
        } else {
            cin >> v >> c, --v, --c;
        }
    }
}