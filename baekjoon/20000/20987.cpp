#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct edge {
    int to, colour, price;
    edge(int to, int colour, int price) : to(to), colour(colour), price(price) {}
};

struct elem {
    int64_t d;
    int u;
    elem(int64_t d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;

    int n, m;
    cin >> n >> m;

    vector<vector<edge>> adj(n);
    for (int u, v, c, p, i = m; i--;) {
        cin >> u >> v >> c >> p, --u, --v, --c;
        adj[u].emplace_back(v, c, p);
        adj[v].emplace_back(u, c, p);
    }

    vector<int64_t> dist(n, INF), sum(m), prv(m, INF);

    priority_queue<elem> pq;
    pq.emplace(dist[0] = 0, 0);

    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (const auto& [v, c, p] : adj[u]) {
            sum[c] += p;
            chmin(prv[c], dist[v]);
        }

        for (const auto& [v, c, p] : adj[u]) {
            const auto d2 = min(d + min(int64_t(p), sum[c] - p), prv[c] + sum[c] - p);
            if (dist[v] > d2)
                pq.emplace(dist[v] = d2, v);
        }

        for (const auto& [v, c, p] : adj[u])
            sum[c] = 0, prv[c] = INF;
    }

    cout << (dist.back() == INF ? -1 : dist.back());
}