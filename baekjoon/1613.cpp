#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool adj[401][401];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u][v] = true;
    }

    // Bellman-Ford
    for (int i = 1; i <= V; ++i)
        adj[i][i] = true;
    for (int k = 1; k <= V; ++k)
        for (int i = 1; i <= V; ++i)
            for (int j = 1; j <= V; ++j)
                adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
    cin >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        if (adj[u][v]) cout << -1;
        else if (adj[v][u]) cout << 1;
        else cout << 0;
        cout << '\n';
    }
    return 0;
}