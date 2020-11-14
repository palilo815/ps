#include <bits/stdc++.h>
using namespace std;

const int mxN = 2500;

int adj[mxN][mxN], dist[mxN], par[mxN];
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

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> adj[i][j];

    move(adj[0], adj[0] + N, dist);
    con[0] = true;
    dist[0] = INT_MAX;

    for (int cnt = N - 1; cnt--;) {
        int u = 0;
        for (int i = 1; i < N; ++i)
            if (!con[i] && dist[i] < dist[u])
                u = i;

        cout << u + 1 << ' ' << par[u] + 1 << '\n';
        con[u] = true;

        for (int v = 1; v < N; ++v)
            if (!con[v] && adj[u][v] < dist[v])
                dist[v] = adj[u][v], par[v] = u;
    }
}