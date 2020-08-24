#include <bits/stdc++.h>
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 1e4 + 1;
const int mxM = 1e5;

int par[mxN];
edge e[mxM];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int i = 0; i < M; ++i)
        cin >> e[i].u >> e[i].v >> e[i].w;
    int x1, x2; cin >> x1 >> x2;

    sort(e, e + M, [&](auto & a, auto & b) {
        return a.w > b.w;
    });
    memset(par + 1, -1, sizeof(int) * N);

    int ans = 0;
    for (int i = 0, u, v; _find(x1) ^ _find(x2); ++i) {
        u = _find(e[i].u), v = _find(e[i].v), ans = e[i].w;
        if (u ^ v) par[u] = v;
    }
    cout << ans;
    return 0;
}