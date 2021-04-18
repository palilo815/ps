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
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    auto vtx = [&](int src) {
        vector<int> stk = {src}, vtx(n);

        for (int i = 0; i < n; ++i) {
            const auto u = stk.back();
            stk.pop_back();

            vtx[i] = u;
            for (const auto& v : adj[u]) {
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                stk.emplace_back(v);
            }
        }
        reverse(vtx.begin(), vtx.end());
        return vtx;
    }(0);

    vector<int> dp(n);
    auto valid = [&](int mid) {
        for (const auto& u : vtx) {
            dp[u] = accumulate(adj[u].begin(), adj[u].end(), 0, [&](auto& sum, auto& v) {
                return sum + dp[v] + 1;
            });
            dp[u] = dp[u] < mid ? 0 : dp[u] - mid;
        }
        return dp[0] == 0;
    };

    int lo = 0, hi = n;
    while (lo != hi) {
        int mid = (lo + hi) >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}