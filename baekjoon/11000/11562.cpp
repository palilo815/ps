#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int INF = 987654321;
const int max_N = 250;
int adj[max_N + 1][max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** Floyd-Warshall **
    int V, E; cin >> V >> E;
    LOOP(i, V) LOOP(j, V) adj[i][j] = INF;
    LOOP(i, V) adj[i][i] = 0;

    // u->v는 무조건 지나갈 수 있으므로 비용 0
    // 양방향 길인경우 v->u == 0,
    // 단방향 길인경우 v->u == 1 (지나가려면 비용을 1 써서 양방향 길로 바꿔야 한다.)
    while (E--) {
        int u, v, B; cin >> u >> v >> B;
        adj[u][v] = 0;
        adj[v][u] = 1 - B;
    }

    // ** Floyd-Warshall **
    LOOP(k, V) LOOP(i, V) LOOP(j, V)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

    int k; cin >> k;
    while (k--) {
        int u, v; cin >> u >> v;
        cout << adj[u][v] << '\n';
    }
    return 0;
}