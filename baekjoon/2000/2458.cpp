#include<bits/stdc++.h>
using namespace std;
#define LOOP(i,n) for(int i=1;i<=n;++i)

bool adj[501][501], rev[501][501];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u][v] = true;
        rev[v][u] = true;
    }
    LOOP(i, V)
        adj[i][i] = rev[i][i] = true;

    // Floyd-Warshall
    LOOP(k, V) LOOP(i, V) LOOP(j, V) {
        adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
        rev[i][j] = rev[i][j] || (rev[i][k] && rev[k][j]);
    }

    int ans = V;
    LOOP(i, V) LOOP(j, V)
        if (!adj[i][j] && !rev[i][j]) {
            --ans;
            break;
        }
    cout << ans;
    return 0;
}