#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct elem {
    ll d;
    int u;
    elem(ll d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d < rhs.d;
    }
};

const int mxN = 1e5 + 1;

vector<pair<int, int>> adj[mxN];
int h[mxN];
ll dist[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, X;
    cin >> N >> M >> X;

    for (int i = 1; i <= N; ++i)
        cin >> h[i];

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        if (h[u] >= w) adj[u].emplace_back(w, v);
        if (h[v] >= w) adj[v].emplace_back(w, u);
    }

    memset(dist + 1, 0xc0, sizeof(ll) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[1] = X, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        if (u == N) return cout << X + h[N] - d * 2, 0;

        for (auto& [w, v] : adj[u])
            if (dist[v] < min(d - w, (ll)h[v]))
                pq.emplace(dist[v] = min(d - w, (ll)h[v]), v);
    }
    cout << -1;
    return 0;
}