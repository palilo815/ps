#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 1e3;

int lo[mxN][mxN], hi[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, Q;
    for (;;) {
        cin >> N >> M >> Q;
        if (!N) break;

        for (int i = 0; i < N; ++i) {
            memset(lo[i], 0xc0, sizeof(int) * M);
            memset(hi[i], 0x3f, sizeof(int) * M);
        }

        bool ok = true;
        char op[3];

        for (int u, v, w; Q--;) {
            cin >> u >> v >> op >> w;
            if (!ok) continue;
            --u, --v;

            if (op[0] == '<') {
                if (lo[u][v] > w) ok = false;
                hi[u][v] = min(hi[u][v], w);
            } else {
                if (hi[u][v] < w) ok = false;
                lo[u][v] = max(lo[u][v], w);
            }
        }

        cout << (ok ? "Possible\n" : "Impossible\n");
    }
    return 0;
}