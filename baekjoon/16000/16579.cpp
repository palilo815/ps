#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MX_N = 500;

    int n, m;
    cin >> n >> m;

    array<array<bool, MX_N>, MX_N> con {};
    vector<int> deg(n);

    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        con[u][v] = true;
        ++deg[u], ++deg[v];
    }

    vector<pair<int, int>> edges;
    for (int u = 0; u < n - 1; ++u)
        for (int v = u + 1; v < n; ++v)
            if (!con[u][v])
                edges.emplace_back(u, v);

    int ans = (n - 2) << 1;
    while (!edges.empty()) {
        auto mx = *max_element(edges.begin(), edges.end(), [&](auto& a, auto& b) {
            return deg[a.first] + deg[a.second] < deg[b.first] + deg[b.second];
        });
        chmin(ans, deg[mx.first] + deg[mx.second]);

        auto pivot = remove_if(edges.begin(), edges.end(), [&](auto& e) {
            if (deg[e.first] + deg[e.second] < ans) return false;
            ++deg[e.first], ++deg[e.second];
            return true;
        });
        edges.erase(pivot, edges.end());
    }
    cout << ans << '\n';
}