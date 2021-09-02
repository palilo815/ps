#include <bits/stdc++.h>
using namespace std;

struct edge_t {
    int v, rev, cap;
    edge_t(int v, int rev, int cap) : v(v), rev(rev), cap(cap) {}
};

constexpr int MX_N = 100;
constexpr int MX_VTX = MX_N * 2 + 2;
constexpr int s = 0, t = 1;

vector<edge_t> g[MX_VTX];
int n, vtx, a[MX_N], level[MX_VTX], ptr[MX_VTX];
bool danger[MX_N];
char buf[MX_N + 1];

inline int land1(int i) { return 2 * i + 2; }
inline int land2(int i) { return 2 * i + 3; }

void add_edge(int u, int v, int c) {
    g[u].emplace_back(v, g[v].size(), c);
    g[v].emplace_back(u, g[u].size() - 1, 0);
}

int bfs() {
    memset(level, 0, sizeof(int) * vtx);
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
    for (auto& [v, rev, cap] : g[u]) {
        if (cap && level[u] + 1 == level[v]) {
            if (const auto d = dfs(v, min(f, cap)); d) {
                return cap -= d, g[v][rev].cap += d, d;
            }
        }
    }
    return 0;
}

int dinitz(int lim) {
    const auto index = [&](int land) { return land / 2 - 1; };
    for (auto& [v, rev, cap] : g[s]) {
        cap = a[index(v)];
    }
    for (auto& [v, rev, cap] : g[t]) {
        cap = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (auto& [v, rev, cap] : g[land1(i)]) {
            cap = v == s ? 0 : INT_MAX;
        }
        for (auto& [v, rev, cap] : g[land2(i)]) {
            cap = v == t ? (danger[i] ? lim : 1) : 0;
        }
    }
    int ret = 0;
    for (int f; bfs();) {
        memset(ptr, 0, sizeof(int) * vtx);
        while ((f = dfs(s, INT_MAX))) ret += f;
    }
    return ret;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vtx = 2 * n + 2;
    for_each(g, g + vtx, [&](auto& x) { x.clear(); });
    for (int i = 0; i < n; ++i) {
        if (!a[i]) continue;
        add_edge(s, land1(i), a[i]);
        add_edge(land2(i), t, 1);
        add_edge(land1(i), land2(i), INT_MAX);
    }
    memset(danger, 0, n);
    for (int i = 0; i < n; ++i) {
        cin >> buf;
        if (!a[i]) continue;
        for (int j = 0; j < n; ++j) {
            if (buf[j] == 'Y') {
                if (a[j]) {
                    add_edge(land1(i), land2(j), INT_MAX);
                } else {
                    danger[i] = true;
                }
            }
        }
    }
    const int num_danger = count(danger, danger + n, true),
              num_safe = count_if(a, a + n, [&](const auto&x) { return x; }) - num_danger;
    int lo = 1, hi = accumulate(a, a + n, 0);
    while (lo != hi) {
        const auto mid = (lo + hi + 1) >> 1;
        (dinitz(mid) == num_safe + mid * num_danger) ? lo = mid : hi = mid - 1;
    }
    cout << lo << '\n';
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