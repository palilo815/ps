#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;
struct elem {
    p d;
    int u;
    elem(int dist, int dust, int u) : d(dist, dust), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e3 + 2;

vector<p> adj[mxN];
int mn_dist[mxN], mn_dust[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;
    N += 2;

    for (int u, v, w; K--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    memset(mn_dist, 0x3f, sizeof(int) * N);
    memset(mn_dust, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(mn_dist[0] = 0, mn_dust[0] = 0, 0);

    for (;;) {
        auto [d, u] = pq.top();
        auto& [dist, dust] = d;
        pq.pop();

        if (dist > mn_dist[u] && dust > mn_dust[u]) continue;
        if (u == N - 1) return cout << dist, 0;

        if (dust && mn_dust[u])
            pq.emplace(dist + 5, mn_dust[u] = 0, u);
        for (auto& [v, w] : adj[u]) {
            if (dust + w > 100) continue;
            bool go = false;
            if (mn_dist[v] > dist + w) mn_dist[v] = dist + w, go = true;
            if (mn_dust[v] > dust + w) mn_dust[v] = dust + w, go = true;
            if (go) pq.emplace(dist + w, dust + w, v);
        }
    }
}