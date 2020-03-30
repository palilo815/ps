#include<bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_V = 400;
const int INF = 0x3f3f3f3f;

int adj[max_V + 1][max_V + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    memset(adj, 0x3f, sizeof(adj));
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u][v] = w;
    }

    LOOP(k, V) LOOP(i, V) LOOP(j, V)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    int ans = INF;
    LOOP(i, V) ans = min(ans, adj[i][i]);
    cout << (ans == INF ? -1 : ans);
    return 0;
}