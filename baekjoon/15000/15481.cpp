#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;

struct edge {
    int u, v, w, i;
};

edge e[mxN];
int ans[mxN];

struct disjoint_set {
    int64_t mst;
    vector<int> par, dist;
    disjoint_set(int n) {
        mst = 0;
        par.resize(n, -1);
        dist.resize(n, 0x3f3f3f3f);
    }
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    void merge(edge& e) {
        int u = find(e.u), v = find(e.v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        dist[v] = e.w;
        mst += e.w;
    }
    int query(int u, int v) {
        int ans;
        for (; u != v; u = par[u]) {
            if (dist[u] > dist[v]) swap(u, v);
            ans = dist[u];
        }
        return ans;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        --e[i].u, --e[i].v, e[i].i = i;
    }

    sort(e, e + M, [&](auto& a, auto& b) {
        return a.w < b.w;
    });

    disjoint_set dsu(N);
    for (int i = 0; i < M; ++i)
        dsu.merge(e[i]);
    for (int i = 0; i < M; i++)
        ans[e[i].i] = e[i].w - dsu.query(e[i].u, e[i].v);
    for (int i = 0; i < M; ++i)
        cout << dsu.mst + ans[i] << '\n';
}