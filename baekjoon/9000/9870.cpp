#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef long long ll;

const int max_N = 200;
const ll INF = INT64_MAX / 4;

ll dist[max_N + 1][max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K, Q; cin >> N >> M >> K >> Q;
    LOOP(i, N) LOOP(j, N) if (i != j)
        dist[i][j] = INF;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        dist[u][v] = w;
    }

    LOOP(k, N) LOOP(i, N) LOOP(j, N)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int cnt = 0;
    ll sum = 0;
    while (Q--) {
        int u, v; cin >> u >> v;
        ll cost = INF;
        LOOP(k, K) cost = min(cost, dist[u][k] + dist[k][v]);
        if (cost != INF)
            ++cnt, sum += cost;
    }
    cout << cnt << '\n' << sum;
    return 0;
}