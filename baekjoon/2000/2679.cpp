#include <bits/stdc++.h>
using namespace std;

struct edge_t {
    int v, rev, cap;
    edge_t(int v, int rev, int cap) : v(v), rev(rev), cap(cap) {}
};

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& o) const { return d < o.d; }
};

constexpr int MX_N = 1e3;

int n, m, s, t;
vector<pair<int, int>> adj[MX_N];
vector<edge_t> g[MX_N];
int dist[MX_N], level[MX_N], ptr[MX_N];

int dijk() {
    memset(dist, -1, sizeof(int) * n);
    priority_queue<elem> pq;
    pq.emplace(dist[s] = INT_MAX, s);
    for (;;) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        if (u == t) return d;
        for (const auto& [w, v] : adj[u]) {
            if (const auto d2 = min(d, w); dist[v] < d2) {
                pq.emplace(dist[v] = d2, v);
            }
        }
    }
    assert(false);
    return -1;
}

void add_edge(int u, int v, int w) {
    g[u].emplace_back(v, g[v].size(), w);
    g[v].emplace_back(u, g[u].size() - 1, 0);
}

int bfs() {
    memset(level, 0, sizeof(int) * n);
    level[s] = 1;
    queue<int> q;
    q.emplace(s);
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        for (const auto& [v, rev, cap] : g[u]) {
            if (cap && !level[v]) {
                level[v] = level[u] + 1;
                q.emplace(v);
            }
        }
    }
    return level[t];
}

int dfs(int u, int f) {
    if (u == t) return f;
    for (int &i = ptr[u], sz = g[u].size(); i < sz; ++i) {
        auto& [v, rev, cap] = g[u][i];
        if (cap && level[v] == level[u] + 1) {
            if (const auto d = dfs(v, min(f, cap)); d) {
                return cap -= d, g[v][rev].cap += d, d;
            }
        }
    }
    return 0;
}

int dinitz() {
    int ret = 0;
    for (int f; bfs();) {
        memset(ptr, 0, sizeof(int) * n);
        while ((f = dfs(s, INT_MAX))) ret += f;
    }
    return ret;
}

void solve() {
    cin >> n >> m >> s >> t;
    for_each(adj, adj + n, [&](auto& x) { x.clear(); });
    for_each(g, g + n, [&](auto& x) { x.clear(); });
    for (int u, v, w; m--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        add_edge(u, v, w);
    }
    const auto p = dinitz(), q = dijk();
    cout << double(p) / q << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cout << fixed << setprecision(3);
    int T;
    cin >> T;
    while (T--) solve();
}