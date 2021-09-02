#include <bits/stdc++.h>
using namespace std;

struct edge_t {
    int v, rev, cap;
    edge_t(int v, int rev, int cap) : v(v), rev(rev), cap(cap) {}
};

constexpr int MX_W = 50;
constexpr int MX_N = MX_W * MX_W + 2;

int s, t, n;
char grid[MX_W][MX_W];
vector<edge_t> g[MX_N];
int level[MX_N], ptr[MX_N];

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
        if (cap && level[u] + 1 == level[v]) {
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
    int w, h, d, f, b;
    cin >> w >> h >> d >> f >> b;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> grid[i][j];
        }
    }
    s = w * h, t = w * h + 1, n = w * h + 2;
    for_each(g, g + n, [&](auto& x) { x.clear(); });
    int ans = 0;
    for (int i = 0; i < w; ++i) {
        if (grid[0][i] == '.') ans += f;
        if (grid[h - 1][i] == '.') ans += f;
        add_edge(s, i, INT_MAX);
        add_edge(s, (h - 1) * w + i, INT_MAX);
    }
    for (int i = 1; i < h - 1; ++i) {
        if (grid[i][0] == '.') ans += f;
        if (grid[i][w - 1] == '.') ans += f;
        add_edge(s, i * w, INT_MAX);
        add_edge(s, i * w + w - 1, INT_MAX);
    }
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            if (grid[i][j] == '.') {
                add_edge(i * w + j, t, f);
            } else {
                add_edge(s, i * w + j, d);
            }
        }
    }
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j + 1 != w) {
                add_edge(i * w + j, i * w + j + 1, b), add_edge(i * w + j + 1, i * w + j, b);
            }
            if (i + 1 != h) {
                add_edge(i * w + j, (i + 1) * w + j, b), add_edge((i + 1) * w + j, i * w + j, b);
            }
        }
    }
    cout << ans + dinitz() << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}