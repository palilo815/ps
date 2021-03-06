#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0, u, v; i < n; ++i) {
        cin >> u, --u;
        for (;;) {
            cin >> v;
            if (v == -1) break;
            adj[u].emplace_back(v - 1);
        }
    }
    for (auto& vt : adj)
        sort(vt.begin(), vt.end());

    int root;
    cin >> root, --root;

    vector<int> in(n), out(n);
    int t = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        in[u] = ++t;
        for (const auto& v : adj[u])
            if (v != p)
                dfs(v, u);
        out[u] = ++t;
    };
    dfs(root, -1);

    for (int i = 0; i < n; ++i)
        cout << i + 1 << ' ' << in[i] << ' ' << out[i] << '\n';
}