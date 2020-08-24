#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1000;

int adj[mxN][mxN], par[mxN], dist[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;

    vector<pair<int, int>> edge(M);
    for (auto& [u, v] : edge) cin >> u >> v;

    loop(i, N) loop(j, N) cin >> adj[i][j];
    for (auto& [u, v] : edge)
        adj[u - 1][v - 1] = adj[v - 1][u - 1] = 0;

    edge.clear();

    copy(adj[1], adj[1] + N, dist);
    dist[0] = INT_MAX;

    fill(par + 2, par + N, 1);

    int cnt = N - 2, ans = 0;
    while (cnt--) {
        int k = 0;
        for (int i = 2; i < N; ++i)
            if (par[i] && dist[i] < dist[k])
                k = i;

        ans += dist[k];
        if (dist[k]) edge.emplace_back(par[k], k);
        par[k] = 0;

        for (int i = 2; i < N; ++i)
            if (par[i] && dist[i] > adj[k][i])
                dist[i] = adj[k][i], par[i] = k;
    }

    cout << ans << ' ' << edge.size();
    for (auto& [u, v] : edge) cout << '\n' << u + 1 << ' ' << v + 1;
    return 0;
}