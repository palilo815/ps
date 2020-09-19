#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 100;
const int oo = 0x3f3f3f3f;

int e[mxN], s[mxN], adj[mxN][mxN];
double cost[mxN][mxN];

void solve() {
    int N, Q;
    cin >> N >> Q;
    loop(i, N) cin >> e[i] >> s[i];
    loop(i, N) loop(j, N) cin >> adj[i][j];
    loop(i, N) loop(j, N) if (adj[i][j] == -1)
        adj[i][j] = oo;

    loop(k, N) loop(i, N) if (adj[i][k] ^ oo)
        loop(j, N) if (adj[k][j] ^ oo)
            adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    loop(i, N) fill(cost[i], cost[i] + N, DBL_MAX);
    loop(i, N) loop(j, N) if (adj[i][j] <= e[i])
        cost[i][j] = min(cost[i][j], 1.0 * adj[i][j] / s[i]);

    loop(k, N) loop(i, N) if (cost[i][k] != DBL_MAX)
        loop(j, N) if (cost[k][j] != DBL_MAX)
            cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

    for (int u, v; Q--;) {
        cin >> u >> v;
        cout << fixed << setprecision(9) << ' ' << cost[u - 1][v - 1];
    }
    cout << '\n';
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
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ':';
        solve();
    }
    return 0;
}