#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 2e2;

int adj[mxN][mxN], cost[mxN], par[mxN];
bool con[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    int ans = 0;
    loop(i, N) loop(j, N) {
        cin >> adj[i][j];
        if (adj[i][j] < 0) {
            ans -= adj[i][j];
            adj[i][j] = 0;
        }
    }

    ans >>= 1;

    move(adj[0], adj[0] + N, cost);
    con[0] = true;

    vector<pair<int, int>> edge;

    loop(_, N - 1) {
        int k = 0;
        loop(i, N) if (!con[i] && (!k || cost[i] < cost[k]))
            k = i;

        ans += cost[k];
        con[k] = true;

        if (cost[k]) edge.emplace_back(k, par[k]);

        loop(i, N) if (!con[i] && adj[k][i] < cost[i])
            cost[i] = adj[k][i],
            par[i] = k;
    }

    cout << ans << ' ' << edge.size() << '\n';
    for (auto& [u, v] : edge) cout << u + 1 << ' ' << v + 1 << '\n';
}