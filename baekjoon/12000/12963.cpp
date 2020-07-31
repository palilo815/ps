#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v;
};

const int mx = 2e3;
const int mod = 1e9 + 7;

int par[mx];
bool ans[mx];
edge e[mx];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, M) cin >> e[i].u >> e[i].v;
    memset(par, -1, sizeof(int) * N);

    for (int i = M - 1; ~i; --i) {
        int u = _find(e[i].u), v = _find(e[i].v);
        if (u == v) continue;

        if (u > v) swap(u, v);
        (u == _find(0) && v == _find(N - 1)) ? (ans[i] = true) : (par[u] = v);
    }

    int res = 0, x = 1;
    loop(i, M) {
        if (ans[i]) res = (res + x) % mod;
        x = (3ll * x) % mod;
    }
    cout << res;
    return 0;
}