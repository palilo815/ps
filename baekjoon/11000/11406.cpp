#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int v, capa, rev;
    edge(int v, int capa, int rev) : v(v), capa(capa), rev(rev) {}
};

const int mx = 100;
const int src = 0;
const int sink = 201;

vector<edge> adj[(mx + 1) << 1];
int level[(mx + 1) << 1], ptr[(mx + 1) << 1];

void add_edge(int u, int v, int c) {
    adj[u].emplace_back(v, c, adj[v].size());
    adj[v].emplace_back(u, 0, adj[u].size() - 1);
}
int bfs() {
    memset(level, -1, sizeof(level));
    level[src] = 0;

    queue<int> q;
    q.emplace(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& [v, capa, _] : adj[u])
            if (capa && level[v] == -1) {
                level[v] = level[u] + 1;
                q.emplace(v);
            }
    }
    return ~level[sink];
}
int dfs(int u, int f) {
    if (u == sink) return f;
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

    int N, M; cin >> N >> M;
    for (int i = mx + 1, c; i <= mx + N; ++i) {
        cin >> c;
        add_edge(i, sink, c);
    }
    for (int i = 1, c; i <= M; ++i) {
        cin >> c;
        add_edge(src, i, c);
    }
    for (int u = 1, c; u <= M; ++u)
        for (int v = mx + 1; v <= mx + N; ++v) {
            cin >> c;
            if (c) add_edge(u, v, c);
        }

    int ans = 0;
    for (int f; bfs();) {
        memset(ptr, 0, sizeof(ptr));
        while ((f = dfs(0, INT_MAX))) ans += f;
    }
    cout << ans;
    return 0;
}