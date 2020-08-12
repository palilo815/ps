#include <bits/stdc++.h>
using namespace std;
struct edge {
    int v, capa, rev;
    edge(int v, int capa, int rev) : v(v), capa(capa), rev(rev) {}
};

const int mx = 501;

vector<edge> adj[mx];
int N, s, t, level[mx], ptr[mx];

void add_edge() {
    int u, v, capa; cin >> u >> v >> capa;
    adj[u].emplace_back(v, capa, adj[v].size());
    adj[v].emplace_back(u, 0, adj[u].size() - 1);

    adj[v].emplace_back(u, capa, adj[u].size());
    adj[u].emplace_back(v, 0, adj[v].size() - 1);
}
int bfs() {
    memset(level + 1, -1, sizeof(int) * N);
    level[s] = 0;

    queue<int> q;
    q.emplace(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& [v, capa, _] : adj[u])
            if (capa && level[v] == -1) {
                level[v] = level[u] + 1;
                q.emplace(v);
            }
    }
    return ~level[t];
}
int dfs(int u, int f) {
    if (u == t) return f;
    for (int& i = ptr[u], sz = adj[u].size(); i ^ sz; ++i) {
        auto& [v, capa, rev] = adj[u][i];
        if (capa && level[u] + 1 == level[v]) {
            int d = dfs(v, min(f, capa));
            if (d) {
                capa -= d;
                adj[v][rev].capa += d;
                return d;
            }
        }
    }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int M; cin >> N >> M;
    while (M--) add_edge();

    cin >> s >> t;
    int ans = 0;
    for (int f; bfs();) {
        memset(ptr + 1, 0, sizeof(int) * N);
        while ((f = dfs(s, INT_MAX))) ans += f;
    }
    cout << ans;
    return 0;
}