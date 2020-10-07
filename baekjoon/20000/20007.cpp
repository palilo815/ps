#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e3;

vector<pair<int, int>> adj[mxN];
int dist[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, X, Y;
    cin >> N >> M >> X >> Y;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        w <<= 1;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(dist, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[Y] = 0, Y);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        for (auto& [w, v] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }

    sort(dist, dist + N);
    if (dist[N - 1] > X) return cout << -1, 0;

    int ans = 1;
    for (int i = 0, s = 0; i < N; ++i) {
        if (s + dist[i] > X) s = 0, ++ans;
        s += dist[i];
    }
    cout << ans;
    return 0;
}