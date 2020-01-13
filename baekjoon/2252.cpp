#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool visited[32001];
vector<int> adj[32001];
stack<int> Ans;

// 평범한 topological sorting
void DFS(int start)
{
    visited[start] = true;
    loop(i, adj[start].size()) {
        int next = adj[start][i];
        if (!visited[next])
            DFS(next);
    }
    Ans.push(start);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= V; ++i)
        if (!visited[i])
            DFS(i);
    while (!Ans.empty()) {
        cout << Ans.top() << ' ';
        Ans.pop();
    }
    return 0;
}