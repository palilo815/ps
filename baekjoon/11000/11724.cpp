#include <bits/stdc++.h>
using namespace std;

const int mxN = 1001;

int par[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int V, E; cin >> V >> E;
    memset(par + 1, -1, sizeof(int) * V);
    for (int i = 0, u, v; i < E; ++i) {
        cin >> u >> v;
        u = _find(u), v = _find(v);
        if (u ^ v) par[u] = v;
    }
    cout << count(par + 1, par + 1 + V, -1);
    return 0;
}