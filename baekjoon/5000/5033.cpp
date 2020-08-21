#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e4;

int par[mxN], a[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> a[i];

    memset(par, -1, sizeof(int) * N);
    loop(i, M) {
        int u, v; cin >> u >> v;
        u = _find(u), v = _find(v);
        if (u ^ v) par[u] = v;
    }

    loop(i, N) if (~par[i])
        a[_find(i)] += a[i];

    bool flag = false;
    loop(i, N) if (par[i] == -1 && a[i]) {
        flag = true;
        break;
    }
    cout << (flag ? "IMPOSSIBLE" : "POSSIBLE");
    return 0;
}