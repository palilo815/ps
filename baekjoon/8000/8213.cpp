#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<bool> d(n);
    for (auto&& x : d) {
        char c;
        cin >> c;
        x = c == '1';
    }

    if (count(d.begin(), d.end(), true) <= m)
        return cout << 0, 0;

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

    // dp_dyn[i] : maximum distance from i to dynamite in sub[i]
    // dp_fus[i] : minimum distance from i to   fuse   in sub[i]
    vector<int> dp_dyn(n), dp_fus(n);

    // if dp_dyn[i] == -1
    //     1. no dynamites in sub[i]
    //     2. all dynamites in sub[i] are ignited

    auto valid = [&](int lim) {
        fill(dp_dyn.begin(), dp_dyn.end(), -1);
        fill(dp_fus.begin(), dp_fus.end(), 0x3f3f3f3f);
        int k = m;

        for (const auto& u : rev_dfn) {
            for (const auto& v : adj[u]) {
                if (~dp_dyn[v]) dp_dyn[u] = max(dp_dyn[u], dp_dyn[v] + 1);
                dp_fus[u] = min(dp_fus[u], dp_fus[v] + 1);
            }
            if (dp_dyn[u] == -1 && d[u]) dp_dyn[u] = 0;

            if (dp_dyn[u] == lim) {
                if (!k--) return false;
                dp_dyn[u] = -1, dp_fus[u] = 0;
            } else if (dp_dyn[u] + dp_fus[u] <= lim)
                dp_dyn[u] = -1;
        }
        return k || dp_dyn[0] == -1;
    };

    int lo = 1, hi = n >> 1;
    while (lo != hi) {
        int mid = (lo + hi) >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }
    cout << lo;
}