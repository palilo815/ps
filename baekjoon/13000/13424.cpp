#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e2;
const int oo = 0x3f3f3f3f;

int adj[mxN][mxN], total[mxN];

void solve() {
    int N, M;
    cin >> N >> M;

    memset(adj, 0x3f, sizeof(adj));
    loop(i, N) adj[i][i] = 0;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        --u, --v;
        adj[u][v] = adj[v][u] = w;
    }

    loop(k, N) loop(i, N) if (adj[i][k] != oo)
        loop(j, N) if (adj[k][j] != oo)
            adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    int K;
    cin >> K;

    memset(total, 0, sizeof(int) * N);
    for (int src; K--;) {
        cin >> src;
        --src;
        transform(adj[src], adj[src] + N, total, total, plus<>());
    }
    cout << min_element(total, total + N) - total + 1 << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}