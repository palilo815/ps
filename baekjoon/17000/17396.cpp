#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using ll = long long;
struct elem {
    ll d;
    int u;
    elem(ll d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e5;
const ll oo = 0x3f3f3f3f3f3f3f3f;

vector<pair<int, int>> adj[mxN];
bool ward[mxN];
ll dist[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    loop(i, N) cin >> ward[i];
    ward[N - 1] = false;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        if (ward[u] || ward[v]) continue;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    memset(dist, 0x3f, sizeof(ll) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[0] = 0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d) continue;
        if (u == N - 1) break;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }
    cout << (dist[N - 1] == oo ? -1 : dist[N - 1]);
    return 0;
}