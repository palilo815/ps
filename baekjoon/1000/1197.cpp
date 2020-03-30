#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_V = 10000;

vector<p> adj[max_V + 1];
bool added[max_V + 1];
int dist[max_V + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill_n(dist + 1, V, INT_MAX);
    dist[1] = 0;
    long long ans = 0;
    int cnt = V;

    while (cnt--) {
        int u = -1;
        for (int i = 1; i <= V; ++i) if (!added[i] && (u == -1 || dist[i] < dist[u]))
            u = i;

        ans += dist[u];
        added[u] = true;

        for (auto [w, v] : adj[u]) if (!added[v] && dist[v] > w)
            dist[v] = w;
    }
    cout << ans;
    return 0;
}