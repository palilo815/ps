#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int INF = 987654321;
const int max_V = 100;
int adj[max_V][max_V];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    loop(i, V) loop(j, V) adj[i][j] = INF;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u - 1][v - 1] = min(adj[u - 1][v - 1], w);
    }

    loop(i, V) adj[i][i] = 0;
    loop(k, V) loop(i, V) loop(j, V)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    loop(i, V) {
        loop(j, V) {
            if (adj[i][j] < INF) cout << adj[i][j] << ' ';
            else cout << "0 ";
        }
        cout << '\n';
    }
    return 0;
}