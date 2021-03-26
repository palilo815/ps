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
    vector<int> a(n);
    for (int i = 1, p; i < n; ++i) {
        char c;
        cin >> c >> a[i] >> p, --p;
        if (c == 'W') a[i] = -a[i];
        adj[p].emplace_back(i);
    }

    auto dfs = [&](auto&& self, int u) -> int64_t {
        int64_t ret = a[u];
        for (const auto& v : adj[u])
            ret += self(self, v);
        if (ret < 0) ret = 0;
        return ret;
    };
    cout << dfs(dfs, 0);
}