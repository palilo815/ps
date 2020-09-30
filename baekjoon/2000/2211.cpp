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

vector<pair<int, int>> adj[mxN];
int dist[mxN], par[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    memset(dist + 1, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[1] = 0, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w) {
                pq.emplace(dist[v] = d + w, v);
                par[v] = u;
            }
    }

    cout << N - 1 << '\n';
    for (int v = 2; v <= N; ++v)
        cout << v << ' ' << par[v] << '\n';
    return 0;
}