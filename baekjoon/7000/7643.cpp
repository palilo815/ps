#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 1e3;
const int mxQ = 1e4;
const int INF = 0x3f3f3f3f;

edge e[mxQ];
int dist[mxN << 1];

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

        for (int i = 0, lo; i < Q; ++i) {
            cin >> e[i].u >> e[i].v;
            --e[i].u, e[i].v += N - 1;

            cin.ignore();
            lo = cin.get() == '<' ? 1 : 0;
            cin.ignore();

            cin >> e[i].w;

            if (lo) swap(e[i].u, e[i].v);
            else
                e[i].w = -e[i].w;
        }

        memset(dist, 0, sizeof(int) * (N + M));

        bool update;
        for (int cnt = N + M; cnt--;) {
            update = false;
            for (int i = 0; i < Q; ++i)
                if (dist[e[i].v] > dist[e[i].u] + e[i].w) {
                    dist[e[i].v] = dist[e[i].u] + e[i].w;
                    update = true;
                }
            if (!update) break;
        }
        cout << (update ? "Impossible\n" : "Possible\n");
    }
    return 0;
}