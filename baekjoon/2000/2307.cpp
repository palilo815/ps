#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e3 + 1;
const int INF = 0x3f3f3f3f;

vector<pair<int, int>> adj[mxN];
int N, M, dist[mxN], par[mxN];

int dijk(int b1 = 0, int b2 = 0) {
    memset(dist + 1, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[1] = 0, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        if (u == N) return d;

        for (auto& [v, w] : adj[u])
            if ((u != b1 || v != b2) && (u != b2 || v != b1) && dist[v] > d + w) {
                pq.emplace(dist[v] = d + w, v);
                if (b1 == 0) par[v] = u;
            }
    }
    return INF;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M;
    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    dijk();

    int path = dist[N], delay = 0;
    for (int v = N, u; u = par[v]; v = par[v]) {
        int d = dijk(u, v);
        if (d == INF) return cout << -1, 0;
        delay = max(delay, d - path);
    }
    cout << delay;
    return 0;
}