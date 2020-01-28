#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 100000;

vector<int> adj[max_N + 1];
int parent[max_N + 1];
void DFS(int u)
{
    for (int v : adj[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        DFS(v);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V; cin >> V;
    loop(i, V - 1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(1);
    for (int i = 2; i <= V; ++i)
        cout << parent[i] << '\n';
    return 0;
}