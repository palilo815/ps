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

    int n, m, x;
    cin >> n >> m >> x, --x;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    vector dist(n, INF);

    priority_queue<elem> pq;
    pq.emplace(dist[x] = 0, x);

    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (const auto& [w, v] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }

    cout << (*max_element(dist.begin(), dist.end()) << 1);
}