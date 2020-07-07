#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using p = pair<int, int>;

const int max_N = 50001;
const int max_E = 200000;

struct edge {
    int u, v, w, i;
} e[max_E];
vector<p> adj[max_N];

int N, M, t = -1;
int sz[max_N], par[max_N], top[max_N], idx[max_N];
p segT[max_N - 1 << 1];

int parent[max_N];
bool used[max_E];

p _max(p a, p b) {
    if (a.x == b.x) return {a.x, max(a.y, b.y)};
    return {max(a.x, b.x), max(min(a.x, b.x), max(a.y, b.y))};
}
int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
int dfs(int u, int p) {
    for (auto& [w, v] : adj[u])
        if (v ^ p)
            sz[u] += dfs(v, u);
    return ++sz[u];
}
void hld(int u, int p, int d) {
    int H = 0, HD = 0;
    for (auto& [w, v] : adj[u])
        if (v ^ p && sz[v] > sz[H])
            H = v, HD = w;
    for (auto& [w, v] : adj[u])
        if (v ^ p && v ^ H)
            hld(v, u, w);

    if (!top[u]) top[u] = u;
    if (H) top[H] = top[u], hld(H, u, HD);

    par[u] = p, idx[u] = ++t;
    segT[idx[u] + N] = {d, -1};
}
p query(int l, int r) {
    p ret = { -1, -1};
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret = _max(ret, segT[l++]);
        if (r & 1) ret = _max(ret, segT[--r]);
    }
    return ret;
}
p solve(int u, int v) {
    p ret = { -1, -1};
    while (top[u] ^ top[v]) {
        int& n = sz[top[u]] < sz[top[v]] ? u : v;
        ret = _max(ret, query(idx[n], idx[top[n]] + 1));
        n = par[top[n]];
    }
    if (idx[u] > idx[v]) swap(u, v);
    ret = _max(ret, query(idx[u], idx[v]));
    return ret;
}
int build_mst() {
    memset(parent + 1, -1, sizeof(int) * N);
    sort(e, e + M, [&](edge & a, edge & b) -> bool {
        return a.w < b.w;
    });

    int mst = 0, cnt = 0;
    for (int j = 0; j < M; ++j) {
        auto [u, v, w, i] = e[j];
        u = _find(u), v = _find(v);
        if (u ^ v) {
            mst += w, ++cnt, parent[u] = v, used[i] = true;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }
    }
    return cnt == N - 1 ? mst : -1;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].i = i;
    }

    int mst = build_mst();
    if (mst == -1 || M == N - 1) {cout << -1; return 0;}

    dfs(1, 0);
    hld(1, 0, 0);

    for (int i = N - 1; i; --i)
        segT[i] = _max(segT[i << 1], segT[i << 1 | 1]);

    int ans = INT_MAX;
    for (int j = 0; j < M; ++j) {
        auto& [u, v, w, i] = e[j];
        if (!used[i]) {
            auto [w1, w2] = solve(u, v);
            if (w > w1) ans = min(ans, w - w1);
            else if (~w2 && w > w2) ans = min(ans, w - w2);
        }
    }
    cout << (ans == INT_MAX ? -1 : mst + ans);
    return 0;
}