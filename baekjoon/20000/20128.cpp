#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 1e5;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct elem {
    ll d;
    int u;
    elem(ll d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

vector<pair<int, int>> adj[mxN];
ll dist[mxN][2];

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
        --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    priority_queue<elem> pq;

    memset(dist, 0x3f, sizeof(dist));
    pq.emplace(dist[0][0] = 0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (dist[u][d & 1] != d) continue;

        for (auto& [w, v] : adj[u])
            if (dist[v][d + w & 1] > d + w)
                pq.emplace(dist[v][d + w & 1] = d + w, v);
    }

    for (int i = 0; i < N; ++i)
        cout << (dist[i][1] == INF ? -1 : dist[i][1]) << ' ' << (dist[i][0] == INF ? -1 : dist[i][0]) << '\n';
}