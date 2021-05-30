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

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    int p, q;
    cin >> p >> q;

    vector<int> hom(p), con(q);
    for (auto& x : hom) cin >> x, --x;
    for (auto& x : con) cin >> x, --x;

    vector dist(n, INF);

    priority_queue<elem> pq;
    for (const auto& x : con)
        pq.emplace(dist[x] = 0, x);

    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (const auto& [w, v] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }

    cout << *min_element(hom.begin(), hom.end(), [&](auto& l, auto& r) {
        return dist[l] < dist[r];
    }) + 1;
}