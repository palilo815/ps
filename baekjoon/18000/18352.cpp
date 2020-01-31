#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int max_V = 300000;

vector<int> adj[max_V + 1];
int dist[max_V + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, K, src; cin >> V >> E >> K >> src;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    LOOP(i,V) dist[i] = INT_MAX;
    dist[src] = 0;

    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u])
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }

    vector<int> ans;
    LOOP(i, V)
        if (dist[i] == K) ans.push_back(i);
    if (ans.empty()) cout << -1;
    else for (int x : ans) cout << x << '\n';
    return 0;
}