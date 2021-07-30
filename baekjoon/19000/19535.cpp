#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
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
    auto rev_dfn = [&](int root) {
        vector<int> stk = {root}, dfn(n);
        for (auto& u : dfn) {
            u = stk.back();
            stk.pop_back();
            for (const auto& v : adj[u]) {
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                stk.emplace_back(v);
            }
        }
        reverse(dfn.begin(), dfn.end());
        return dfn;
    }(0);
    int64_t d = 0, g = 0;
    for (const auto& u : rev_dfn) {
        const int64_t cnt1 = adj[u].size() + !!u;
        const int64_t cnt2 = accumulate(adj[u].begin(), adj[u].end(), 0, [&](auto& sum, auto& v) {
            return sum + adj[v].size();
        });
        d += cnt2 * (cnt1 - 1);
        g += cnt1 * (cnt1 - 1) * (cnt1 - 2) / 3 / 2;
    }
    if (d > 3 * g) {
        cout << 'D';
    } else if (d < 3 * g) {
        cout << 'G';
    } else {
        cout << "DUDUDUNGA";
    }
}