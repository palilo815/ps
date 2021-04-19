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

    auto rev_dfn = [&](int src) {
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

    int ans = accumulate(adj.begin() + 1, adj.end(), (adj[0].size() + 1) >> 1, [&](auto& sum, auto& vt) {
        return sum + (vt.size() >> 1);
    });

    vector<int> dp(n);
    multiset<int, greater<int>> child;
    auto valid = [&](int lim) {
        fill(dp.begin(), dp.end(), -1);
        for (const auto& u : rev_dfn) {
            child.clear();
            for (const auto& v : adj[u])
                child.emplace(dp[v] + 1);

            if (!!u ^ (child.size() & 1))
                child.emplace_hint(child.end(), 0);

            while (int(child.size()) > 1) {
                auto mx = *child.begin();
                child.erase(child.begin());

                auto it = child.lower_bound(lim - mx);
                if (it == child.end()) {
                    if (~dp[u]) return false;
                    dp[u] = mx;
                } else
                    child.erase(it);
            }
            if (u && !child.empty())
                dp[u] = *child.begin();
        }
        return dp[0] == -1;
    };

    int lo = 1, hi = n - 1;
    while (lo != hi) {
        int mid = (lo + hi) >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << ans << ' ' << lo;
}