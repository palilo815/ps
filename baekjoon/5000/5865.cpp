#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct edge {
    int v, l, c;
    edge(int v, int l, int c) : v(v), l(l), c(c) {}
};
struct elem {
    ll d;
    int u;
    elem(ll d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 500;
const ll oo = 0x3f3f3f3f3f3f3f3f;

vector<edge> adj[mxN];
int N, capa[mxN];
ll dist[mxN];

ll dijk(int mnC) {
    memset(dist, 0x3f, sizeof(ll) * N);
    priority_queue<elem> pq;
    pq.emplace(dist[0] = 0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d) continue;
        if (u == N - 1) return d;

        for (auto& [v, l, c] : adj[u])
            if (c >= mnC && dist[v] > d + l)
                pq.emplace(dist[v] = d + l, v);
    }
    return oo;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int M, X;
    cin >> N >> M >> X;
    for (int u, v, l, c, i = 0; i < M; ++i) {
        cin >> u >> v >> l >> c;
        --u, --v;
        adj[u].emplace_back(v, l, c);
        adj[v].emplace_back(u, l, c);
        capa[i] = c;
    }

    sort(capa, capa + M);
    M = unique(capa, capa + M) - capa;

    ll ans = oo;
    for (int i = 0; i < M; ++i)
        ans = min(ans, dijk(capa[i]) + X / capa[i]);
    cout << ans;
    return 0;
}