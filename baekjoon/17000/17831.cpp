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
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1, p; i < n; ++i) {
        cin >> p, --p;
        adj[p].emplace_back(i);
    }
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto rev_dfn = [&](int root) {
        vector<int> stk = {root}, dfn(n);
        for (auto& u : dfn) {
            u = stk.back();
            stk.pop_back();
            for (const auto& v : adj[u]) {
                stk.emplace_back(v);
            }
        }
        reverse(dfn.begin(), dfn.end());
        return dfn;
    }(0);
    vector<pair<int, int>> dp(n);
    for (const auto& u : rev_dfn) {
        for (const auto& v : adj[u]) {
            dp[u].first += max(dp[v].first, dp[v].second);
        }
        for (const auto& v : adj[u]) {
            chmax(dp[u].second, dp[u].first - max(dp[v].first, dp[v].second) + dp[v].first + a[u] * a[v]);
        }
    }
    cout << max(dp[0].first, dp[0].second);
}