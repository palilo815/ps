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
    vector closest_red(n, INF), fartest_blk(n, -1);
    int red = 0;
    for (const auto& u : rev_dfn) {
        for (const auto& v : adj[u]) {
            chmin(closest_red[u], closest_red[v] + 1);
            chmax(fartest_blk[u], fartest_blk[v] + 1);
        }
        if (closest_red[u] + fartest_blk[u] <= k) {
            fartest_blk[u] = -1;
        } else if (closest_red[u] > k) {
            chmax(fartest_blk[u], 0);
        }
        if (fartest_blk[u] == k) {
            ++red, closest_red[u] = 0, fartest_blk[u] = -1;
        }
    }
    if (~fartest_blk[0]) ++red;
    cout << red;
}