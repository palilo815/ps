#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v, w;
};

const int mxN = 1e5;

int cow[mxN + 1], par[mxN + 1];
edge e[mxN];

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
    for (int i = 1, x; i <= N; ++i) {
        cin >> x;
        cow[x] = i;
    }
    for (int i = 0; i < M; ++i)
        cin >> e[i].u >> e[i].v >> e[i].w;

    sort(e, e + M, [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    memset(par + 1, -1, sizeof(int) * N);
    int lo = -1, hi = M - 1, s = 0;
    while (lo != hi) {
        int m = (lo + hi + 1) >> 1;
        for (int i = s, u, v; i < m; ++i) {
            u = _find(e[i].u), v = _find(e[i].v);
            if (u != v) par[u] = v;
        }

        bool done = true;
        for (int i = 1; i <= N; ++i)
            if (_find(i) != _find(cow[i])) {
                done = false;
                break;
            }

        if (done) {
            memset(par + 1, -1, sizeof(int) * N);
            hi = m - 1, s = 0;
        } else
            lo = s = m;
    }
    cout << (lo == -1 ? -1 : e[lo].w);
}