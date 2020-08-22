#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 1;

char cow[mxN + 1];
int par[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q >> (cow + 1);
    memset(par + 1, -1, sizeof(int) * N);
    for (int i = 1, u, v; i ^ N; ++i) {
        cin >> u >> v;
        if (cow[u] ^ cow[v]) continue;
        u = _find(u), v = _find(v);
        if (u ^ v) par[u] = v;
    }

    for (int u, v; Q--;) {
        char c; cin >> u >> v >> c;
        u = _find(u), v = _find(v);
        cout << (u ^ v || cow[u] == c);
    }
    return 0;
}