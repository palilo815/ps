#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 2e2;
const int oo = 0x3f3f3f3f;

int adj[mxN][mxN], via[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    memset(adj, 0x3f, sizeof(adj));
    memset(via, 0xff, sizeof(via));

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        --u, --v;
        adj[u][v] = adj[v][u] = w;
    }

    loop(k, N) loop(i, N) if (adj[i][k] != oo)
        loop(j, N) if (adj[k][j] != oo && adj[i][j] > adj[i][k] + adj[k][j])
            adj[i][j] = adj[i][k] + adj[k][j],
            via[i][j] = k;

    auto ans = [&](int u, int v) {
        while (~via[u][v]) v = via[u][v];
        return v + 1;
    };

    loop(i, N) {
        loop(j, N) {
            if (i == j)
                cout << "- ";
            else
                cout << ans(i, j) << ' ';
        }
        cout << '\n';
    }
    return 0;
}