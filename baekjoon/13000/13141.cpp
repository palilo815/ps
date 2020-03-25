#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 200;
const int INF = 1 << 29;

int dist[max_N + 1][max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    vector<tup> edge;

    LOOP(i, N) LOOP(j, N) if (i != j)
        dist[i][j] = INF;

    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        edge.emplace_back(u, v, w);
        if (dist[u][v] > w)
            dist[u][v] = dist[v][u] = w;
    }

    LOOP(k, N) LOOP(i, N) LOOP(j, N)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int ans = INT_MAX;
    LOOP(src, N) {
        int cost = 0;
        for (auto [u, v, w] : edge) {
            int U = dist[src][u], V = dist[src][v];
            cost = max(cost, U + V + w);
        }
        ans = min(ans, cost);
    }
    cout << fixed << setprecision(1) << ans / 2.0;
    return 0;
}