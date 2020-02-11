#include <bits/stdc++.h>
using namespace std;

const int max_V = 10000;

vector<int> adj[max_V + 1];
int disc[max_V + 1], low[max_V + 1];
set<int> ap;

int Time;

int DFS_AP(int u, int p) {
    int ret = 0;
    low[u] = disc[u] = ++Time;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!disc[v]) {
            ++ret;
            DFS_AP(v, u);
            if (p != -1 && disc[u] <= low[v])
                ap.insert(u);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], disc[v]);
    }
    return ret;
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

    for (int i = 1; i <= V; ++i) if (!disc[i])
        if (DFS_AP(i, -1) > 1) ap.insert(i);

    cout << ap.size() << '\n';
    for (int i : ap) cout << i << ' ';
    return 0;
}