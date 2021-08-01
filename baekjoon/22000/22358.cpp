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
    int n, m, k, s, t;
    cin >> n >> m >> k >> s >> t, --s, --t;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    vector<int64_t> dp(n, -1), nxt(n);
    dp[s] = 0;
    int64_t ans = -1;
    for (;;) {
        memset(nxt.data(), -1, sizeof(int64_t) * n);
        for (int u = 0; u < n; ++u) {
            if (dp[u] == -1) {
                continue;
            }
            for (const auto& [w, v] : adj[u]) {
                if (u < v) {
                    chmax(dp[v], dp[u] + w);
                } else {
                    chmax(nxt[v], dp[u]);
                }
            }
        }
        chmax(ans, dp[t]);
        if (!k--) {
            break;
        }
        dp.swap(nxt);
    }
    cout << ans;
}