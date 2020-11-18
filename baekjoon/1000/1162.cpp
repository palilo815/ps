#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4;
const int mxK = 20;

struct elem {
    int64_t d;
    int u, k;
    elem(int64_t d, int u, int k) : d(d), u(u), k(k) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

vector<pair<int, int>> adj[mxN + 1];
int64_t dist[mxN + 1][mxK + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, K;
    cin >> N >> M >> K;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(dist, 0x3f, sizeof(dist));

    priority_queue<elem> pq;
    pq.emplace(dist[1][0] = 0, 1, 0);

    for (;;) {
        auto [d, u, skip] = pq.top();
        pq.pop();

        if (d != dist[u][skip]) continue;
        if (u == N) return cout << d, 0;

        for (auto& [w, v] : adj[u]) {
            if (dist[v][skip] > d + w) {
                pq.emplace(dist[v][skip] = d + w, v, skip);
                for (int i = skip + 1; i <= K && dist[v][i] > d + w; ++i)
                    dist[v][i] = d + w;
            }
            if (skip != K && dist[v][skip + 1] > d) {
                pq.emplace(dist[v][skip + 1] = d, v, skip + 1);
                for (int i = skip + 2; i <= K && dist[v][i] > d; ++i)
                    dist[v][i] = d;
            }
        }
    }
}