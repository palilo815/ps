#include <bits/stdc++.h>
using namespace std;

struct edge {
    int u, v;
};

const int mxN = 3e3;

edge e[mxN + 1];
int q[mxN + 1], par[mxN];

int _find(int u) {
    return par[u] < 0 ? u : (par[u] = _find(par[u]));
}
void _union(int i) {
    int u = _find(e[i].u), v = _find(e[i].v);
    if (u == v) return;
    if (u < v) swap(u, v);
    par[v] += par[u];
    par[u] = v;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i)
        cin >> e[i].u >> e[i].v;

    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        q[x] = i;
    }

    for (int i = 0; i < M; ++i) {
        e[i].u = q[e[i].u], e[i].v = q[e[i].v];
        if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
    }

    sort(e, e + M, [&](auto& a, auto& b) {
        return a.u > b.u;
    });
    e[M].u = -1;

    for (int i = N - 1, j = 0; ~i; --i) {
        par[i] = -1;
        while (e[j].u == i) _union(j++);
        q[i] = par[_find(i)] == i - N;
    }

    for (int i = 0; i < N; ++i)
        cout << (q[i] ? "YES\n" : "NO\n");
    return 0;
}