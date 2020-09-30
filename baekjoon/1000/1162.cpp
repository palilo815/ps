#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct elem {
    ll d;
    int u, k;
    elem(ll d, int u, int k) : d(d), u(u), k(k) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e4 + 1;
const int mxK = 20;

vector<pair<int, int>> adj[mxN];
ll dist[mxN][mxK + 1];

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
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    for (int i = 2; i <= N; ++i)
        memset(dist[i], 0x3f, sizeof(ll) * (K + 1));

    priority_queue<elem> pq;
    for (int i = 0; i <= K; ++i)
        pq.emplace(0, 1, i);

    for (;;) {
        auto [d, u, k] = pq.top();
        pq.pop();
        if (d != dist[u][k]) continue;
        if (u == N) return cout << d, 0;

        for (auto& [v, w] : adj[u]) {
            if (dist[v][k] > d + w)
                pq.emplace(dist[v][k] = d + w, v, k);
            if (k != K && dist[v][k + 1] > d)
                pq.emplace(dist[v][k + 1] = d, v, k + 1);
        }
    }
}