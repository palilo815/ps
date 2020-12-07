#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};
struct edge {
    int u, v, w;
};

vector<pair<int, int>> adj[mxN];
edge e[mxN << 1];
int dist[mxN], par[mxN];

void dijk(int K) {
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<elem> pq;

    for (int s; K--;) {
        cin >> s;
        pq.emplace(dist[s - 1] = 0, s - 1);
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto& [w, v] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }
}
void merge(int u, int v, int w) {
    while (par[u] >= 0) u = par[u];
    while (par[v] >= 0) v = par[v];
    if (u == v) return;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
    dist[v] = w;
}
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, K, Q;
    cin >> N >> M >> K >> Q;

    for (int i = 0, w; i < M; ++i) {
        cin >> e[i].u >> e[i].v >> w;
        --e[i].u, --e[i].v;
        adj[e[i].u].emplace_back(w, e[i].v);
        adj[e[i].v].emplace_back(w, e[i].u);
    }

    dijk(K);

    for (int i = 0; i < M; ++i)
        e[i].w = min(dist[e[i].u], dist[e[i].v]);

    sort(e, e + M, [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    memset(par, -1, sizeof(par));
    memset(dist, -1, sizeof(dist));

    for (int i = 0; i < M; ++i)
        merge(e[i].u, e[i].v, e[i].w);

    for (int u, v, ans; Q--;) {
        cin >> u >> v;
        for (--u, --v; u != v; u = par[u]) {
            if (dist[u] < dist[v]) swap(u, v);
            ans = dist[u];
        }
        cout << ans << '\n';
    }
}