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
    constexpr int INF = 0x3f3f3f3f;
    int n, s, p;
    cin >> n >> s >> p, --p;
    vector<vector<int>> adj(n);
    for (int u, v, i = n - 1; i--;) {
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
    }(p);
    rev_dfn.pop_back();
    vector closest(n, INF);
    for (const auto& u : rev_dfn) {
        if (u < s) {
            closest[u] = 0;
        } else {
            for (const auto& v : adj[u]) {
                chmin(closest[u], closest[v] + 1);
            }
        }
    }
    int mn0 = INF, mn1 = INF;
    for (const auto& v : adj[p]) {
        if (closest[v] <= mn0) {
            mn1 = mn0;
            mn0 = closest[v];
        } else if (closest[v] < mn1) {
            mn1 = closest[v];
        }
    }
    assert(mn0 != INF && mn1 != INF);
    cout << (n - mn0 - mn1 - 3);
}