#include <bits/stdc++.h>
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 1001;
const int mxM = 2e4;

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

    sort(e, e + M, [&](auto & a, auto & b) {
        return a.w > b.w;
    });
    memset(par + 1, -1, sizeof(int) * N);

    int ans = 0, cnt = 0;
    for (int i = 0; i < M; ++i) {
        int u = _find(e[i].u), v = _find(e[i].v);
        if (u ^ v) par[u] = v, ans += e[i].w, ++cnt;
    }
    if (cnt != N - 1) ans = -1;
    cout << ans;
    return 0;
}