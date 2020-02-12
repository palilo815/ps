#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_V = 100000;

vector<int> adj[max_V + 1];
int Time;
int disc[max_V + 1], low[max_V + 1];
vector<p> br;

void dfsBR(int u, int p) {
    low[u] = disc[u] = ++Time;
    for (int& v : adj[u]) {
        if (v == p) continue;
        if (!disc[v]) {
            dfsBR(v, u);
            if (disc[u] < low[v])
                br.push_back({ min(u,v), max(u,v) });
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], disc[v]);
    }
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
    for (int i = 1; i <= V; ++i)
        if (!disc[i]) dfsBR(i, -1);
    sort(br.begin(), br.end());
    cout << br.size() << '\n';
    for (p b : br) cout << b.first << ' ' << b.second << '\n';
    return 0;
}