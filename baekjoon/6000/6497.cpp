#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mx = 2e5;

int N, M, par[mx];
edge e[mx];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
void solve() {
    memset(par, -1, sizeof(int) * N);
    int s = 0;
    loop(i, M) cin >> e[i].u >> e[i].v >> e[i].w;
    loop(i, M) s += e[i].w;
    sort(e, e + M, [&](auto & a, auto & b) {
        return a.w < b.w;
    });

    loop(i, M) {
        auto& [u, v, w] = e[i];
        u = _find(u), v = _find(v);
        if (u ^ v) par[u] = v, s -= w;
    }
    cout << s << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    while (1) {
        cin >> N >> M;
        if (!N) break;
        solve();
    }
    return 0;
}