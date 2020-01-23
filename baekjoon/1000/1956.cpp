#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=1;i<=n;++i)

int adj[401][401];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    loop(i, V) loop(j, V) adj[i][j] = INT32_MAX / 2;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u][v] = w;
    }

    //Floyd–Warshall
    loop(k, V) loop(i, V) loop(j, V)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    int Ans = INT32_MAX;
    loop(i, V) Ans = min(Ans, adj[i][i]);
    if (Ans >= (INT32_MAX / 2)) Ans = -1;
    cout << Ans;
    return 0;
}