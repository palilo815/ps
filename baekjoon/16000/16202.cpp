#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 1e3;
const int mxM = 1e4;

int par[mxN];
edge e[mxM];

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
    int N, M, K;
    cin >> N >> M >> K;
    loop(i, M) cin >> e[i].u >> e[i].v;
    loop(i, M)-- e[i].u, --e[i].v, e[i].w = i + 1;

    sort(e, e + M, [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    while (K--) {
        memset(par, -1, sizeof(int) * N);
        int mst = 0, cnt = N - 1, k = -1;
        for (int i = M - 1; cnt && ~i; --i) {
            int u = _find(e[i].u), v = _find(e[i].v);
            if (u ^ v) {
                if (k == -1) k = i;
                --cnt, par[u] = v, mst += e[i].w;
            }
        }

        if (cnt) {
            for (int i = 0; i <= K; ++i)
                cout << "0 ";
            return 0;
        }

        cout << mst << ' ';
        move(e + k + 1, e + M, e + k);
        --M;
    }
    return 0;
}