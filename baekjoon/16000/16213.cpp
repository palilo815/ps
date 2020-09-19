#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 2e5;
const int mxM = 5e5;

edge e[mxM];
int par[mxN + 1], qu[mxN], qv[mxN], lo[mxN], hi[mxN];

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
    int N, M, Q;
    cin >> N >> M >> Q;
    loop(i, M) cin >> e[i].u >> e[i].v >> e[i].w;
    loop(i, Q) cin >> qu[i] >> qv[i];

    sort(e, e + M, [&](auto& a, auto& b) {
        return a.w > b.w;
    });
    fill(hi, hi + Q, M);

    for (;;) {
        vector<vector<int>> vt(M);
        bool done = true;

        loop(i, Q) if (lo[i] ^ hi[i]) {
            vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        memset(par + 1, -1, sizeof(int) * N);
        loop(m, M) {
            int u = _find(e[m].u), v = _find(e[m].v);
            if (u ^ v) par[u] = v;

            for (int& i : vt[m])
                _find(qu[i]) ^ _find(qv[i]) ? (lo[i] = m + 1) : (hi[i] = m);
        }
    }
    loop(i, Q) cout << e[lo[i]].w << '\n';
    return 0;
}