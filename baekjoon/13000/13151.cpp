#include <bits/stdc++.h>
using namespace std;

const int mxM = 25e4;

struct edge {
    int u, v, w;
};

edge e[mxM];

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) {
        par = vector<int>(n, -1);
    }
    int _find(int u) {
        return par[u] < 0 ? u : (par[u] = _find(par[u]));
    }
    bool _union(int u, int v) {
        u = _find(u), v = _find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, l;
    cin >> n >> m >> l;

    for (int i = 0; i < m; ++i)
        cin >> e[i].u >> e[i].v >> e[i].w;

    int k = 0;
    for (int i = 0; i < l; ++i)
        k += e[i].w;

    sort(e, e + m, [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    disjoint_set dset(n + 1);
    int connect = 0;

    for (int i = 0; i < m; ++i)
        if (dset._union(e[i].u, e[i].v)) {
            ++connect;
            if ((k -= e[i].w) < 0) return cout << "impossible", 0;
        }

    cout << (connect == n - 1 ? "possible" : "impossible");
}