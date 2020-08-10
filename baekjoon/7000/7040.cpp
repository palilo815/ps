#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 1e3;
const int mxM = 2e4;
const int INF = 0x3f3f3f3f;

int dist[mxN + 1];
edge e[mxM];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, M2; cin >> N >> M >> M2;
    loop(i, M) cin >> e[i].u >> e[i].v >> e[i].w;
    loop(i, M2) cin >> e[M + i].v >> e[M + i].u >> e[M + i].w;
    loop(i, M2) e[M + i].w = -e[M + i].w;
    M += M2;

    memset(dist + 1, 0x3f, sizeof(int) * N);
    dist[1] = 0;

    bool update = false;
    int cnt = N;
    while (cnt--) {
        update = false;
        loop(i, M) {
            auto& [u, v, w] = e[i];
            if (dist[u] ^ INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                update = true;
            }
        }
        if (!update) break;
    }

    if (update) cout << -1;
    else if (dist[N] == INF) cout << -2;
    else cout << dist[N];
    return 0;
}