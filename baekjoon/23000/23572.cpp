#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto rev_dfn = [&](int root) {
        vector<int> stk(n), dfn(n);
        int ptr = 0;
        stk[ptr++] = root;
        for (auto& u : dfn) {
            u = stk[--ptr];
            for (const auto& v : adj[u]) {
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                stk[ptr++] = v;
            }
        }
        reverse(dfn.begin(), dfn.end());
        return dfn;
    }(0);
    vector<int> dp(n);
    int ans = 0;
    for (const auto& u : rev_dfn) {
        if (adj[u].empty()) {
            dp[u] = k + 1;
            continue;
        }
        int closest = INT_MAX, fartest = INT_MIN;
        for (const auto& v : adj[u]) {
            chmin(closest, dp[v] + 1);
            chmax(fartest, dp[v] + 1);
        }
        dp[u] = closest + fartest > 2 * k + 1 ? fartest : closest;
        if (dp[u] == 2 * k + 1) {
            ++ans, dp[u] = 0;
        }
    }
    cout << ans + (dp[0] > k);
}