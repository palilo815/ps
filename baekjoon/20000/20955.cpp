#include <bits/stdc++.h>
using namespace std;

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) : par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    int ans = -1;
    disjoint_set dsu(n);
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        if (!dsu.merge(u, v))
            ++ans;
    }

    cout << ans + count_if(dsu.par.begin(), dsu.par.end(), [&](auto& x) { return x < 0; });
}