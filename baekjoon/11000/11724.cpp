#include <bits/stdc++.h>
using namespace std;
const int max_N = 1000;

vector<int> adj[max_N + 1];
bool visited[max_N + 1];
void DFS(int u)
{
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v])
            DFS(v);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = 0;
    for (int i = 1;i <= V;++i)
        if (!visited[i]) {
            DFS(i);
            ++ans;
        }
    cout << ans;
    return 0;
}