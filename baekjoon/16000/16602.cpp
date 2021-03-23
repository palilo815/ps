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

    vector<vector<int>> rev(n);
    vector<int> t(n);
    for (int v = 0, m, u; v < n; ++v)
        for (cin >> t[v] >> m; m--;) {
            cin >> u, --u;
            rev[v].emplace_back(u);
        }

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](auto& a, auto& b) {
        return t[a] > t[b];
    });

    vector<int> stk;
    vector<bool> visited(n);
    int pre = -1;
    auto dfs = [&](int u) {
        visited[u] = true;
        stk.emplace_back(u);

        while (!stk.empty()) {
            const auto u = stk.back();
            stk.pop_back();

            ++pre;

            for (const auto& v : rev[u])
                if (!visited[v]) {
                    visited[v] = true;
                    stk.emplace_back(v);
                }
        }
    };

    int ans = 0;
    for (const auto& u : idx)
        if (!visited[u]) {
            dfs(u);
            ans = max(ans, t[u] + pre);
        }
    cout << ans;
}