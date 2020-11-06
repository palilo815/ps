#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge {
    int u, v, w;
};
struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) {
        par = vector<int>(n, -1);
    }
    int _find(int u) {
        return par[u] < 0 ? u : (par[u] = _find(par[u]));
    }
    // return the number of edges
    int _union(int u, int v) {
        u = _find(u), v = _find(v);
        if (u == v) return 0;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return -par[u] - 1;
    }
};

const int mxN = 1e5;

edge e[mxN - 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    for (int i = 0; i < N - 1; ++i)
        cin >> e[i].u >> e[i].v >> e[i].w;

    sort(e, e + N - 1, [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    disjoint_set dset(N + 1);

    ll ans = 0;
    for (int i = 0; i < N - 1; ++i)
        ans = max(ans, (ll)e[i].w * dset._union(e[i].u, e[i].v));
    cout << ans;
}