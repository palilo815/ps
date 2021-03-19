#include <bits/stdc++.h>
using namespace std;

constexpr int64_t p = 31, m0 = 1e9 + 7, m1 = 1e9 + 9;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<char> c(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        cin >> c[v];
    }

    string key;
    cin >> key;

    int64_t k0 = key[0], k1 = key[0], b0 = 1, b1 = 1;
    for (int i = 1; i < int(key.size()); ++i) {
        k0 = (k0 * p + key[i]) % m0;
        k1 = (k1 * p + key[i]) % m1;

        b0 = b0 * p % m0;
        b1 = b1 * p % m1;
    }

    string s;
    int ans = 0;
    auto dfs = [&](auto&& self, int u, int64_t h0, int64_t h1) -> void {
        if (s.size() >= key.size()) {
            h0 -= s[s.size() - key.size()] * b0 % m0;
            if (h0 < 0) h0 += m0;
            h1 -= s[s.size() - key.size()] * b1 % m1;
            if (h1 < 0) h1 += m1;
        }
        if (u) {
            s += c[u];
            h0 = (h0 * p + c[u]) % m0;
            h1 = (h1 * p + c[u]) % m1;
        }
        if (s.size() >= key.size()) ans += k0 == h0 && k1 == h1;

        for (const auto& v : adj[u])
            self(self, v, h0, h1);
        s.pop_back();
    };
    dfs(dfs, 0, 0, 0);
    cout << ans;
}