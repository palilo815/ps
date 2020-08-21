#include <bits/stdc++.h>
using namespace std;
struct edge {
    int u, v, w;
};

const int mxV = 1e4 + 1;
const int mxE = 1e5;

int par[mxV];
edge e[mxE];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int V, E; cin >> V >> E;
    for (int i = 0; i < E; ++i)
        cin >> e[i].u >> e[i].v >> e[i].w;

    sort(e, e + E, [&](auto & a, auto & b) {
        return a.w < b.w;
    });
    memset(par + 1, -1, sizeof(int) * V);

    int ans = 0;
    for (int i = 0; i < E; ++i) {
        int u = _find(e[i].u), v = _find(e[i].v);
        if (u ^ v) par[u] = v, ans += e[i].w;
    }
    cout << ans;
    return 0;
}