#include <bits/stdc++.h>
using namespace std;
struct edge {
    int u, v;
    edge(int u = 0, int v = 0): u(u), v(v) {}
    bool operator< (const edge& rhs) const {
        return u == rhs.u ? v < rhs.v : u < rhs.u;
    }
    bool operator== (const edge& rhs) const {
        return u == rhs.u && v == rhs.v;
    }
};

const int mxN = 5e4;
const int mxM = 25e4;

const int grey = -1;
const int black = 1;

int N, M, t, par[mxN], visited[mxN];
edge e[mxM + 1];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u ^ v) par[u] = v;
}
bool dfs(int u) {
    visited[u] = grey;
    for (auto it = lower_bound(e, e + M, edge(u, 0)); it->u == u; ++it)
        if (visited[it->v] == grey || (!visited[it->v] && dfs(it->v)))
            return true;
    visited[u] = black;
    return false;
}
bool solve() {
    for (int i = 0; i < N; ++i) {
        int u = _find(i);
        if (!visited[u] && dfs(u))
            return true;
    }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    memset(par, -1, sizeof(int) * N);

    int j = 0;
    for (int i = 0, u, v; i < M; ++i) {
        char c; cin >> u >> c >> v;
        if (c == '=') _union(u, v);
        else e[j++] = {u, v};
    }

    for (int i = 0; i < j; ++i)
        e[i].u = _find(e[i].u), e[i].v = _find(e[i].v);
    sort(e, e + j);
    M = unique(e, e + j) - e;
    e[M].u = -1;

    cout << (solve() ? "in" : "") << "consistent";
    return 0;
}