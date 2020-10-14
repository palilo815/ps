#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5;

int par[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    memset(par, -1, sizeof(int) * N);

    for (int u, v, i = 1; i <= M; ++i) {
        cin >> u >> v;
        u = _find(u), v = _find(v);
        if (u == v)
            return cout << i, 0;
        else
            par[v] = u;
    }
    cout << 0;
    return 0;
}