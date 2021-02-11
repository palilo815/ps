#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 0x3f3f3f3f;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    priority_queue<elem> pq;
    vector<int> d1(n, INF), d2(n, INF);
    vector<bool> visited(n);
    for (int x; k--;) {
        cin >> x;
        pq.emplace(d1[x] = d2[x] = 0, x);
    }

    for (;;) {
        const auto [d, u] = pq.top();
        pq.pop();

        if (u == 0) return cout << d, 0;
        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& [w, v] : adj[u])
            if (d1[v] > d + w) {
                d2[v] = d1[v];
                d1[v] = d + w;
                if (d2[v] != INF) pq.emplace(d2[v], v);
            } else if (d2[v] > d + w)
                pq.emplace(d2[v] = d + w, v);
    }
}