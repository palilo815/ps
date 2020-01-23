#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

vector<int> adj[20001];
bool is_bipartite(int u, vector<bool>& visited, vector<bool>& colour)
{
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            colour[v] = !colour[u];
            if (!is_bipartite(v, visited, colour))
                return false;
        }
        else if (colour[u] == colour[v])
            return false;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, V, E;
    cin >> T;
    while (T--) {
        cin >> V >> E;
        loop(i, V + 1) adj[i].clear();
        while (E--) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // visited : 방문체크
        // colour : 해당 vertex의 색깔
        // DFS 중 같은 색깔끼리 인접하게 되면, 이분그래프가 아니다.
        vector<bool> visited(V + 1), colour(V + 1);
        bool flag = true;
        for (int i = 1; i <= V; ++i)
            if (!visited[i] && !is_bipartite(i, visited, colour)) {
                flag = false;
                break;
            }
        if (flag) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}