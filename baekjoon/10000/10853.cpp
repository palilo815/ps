#include <bits/stdc++.h>
using namespace std;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
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
    constexpr int INF = 0x3f3f3f3f;
    int n, m, k;
    cin >> n >> m >> k;
    cin.ignore();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    vector<bool> dup(n);
    vector dist(n, INF);
    priority_queue<elem> pq;
    pq.emplace(dist[0] = 0, 0);
    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (const auto& [w, v] : adj[u]) {
            if (dist[v] > d + w) {
                dup[v] = dup[u];
                pq.emplace(dist[v] = d + w, v);
            } else if (dist[v] == d + w) {
                dup[v] = true;
            }
        }
    }
    cout << (dup.back() ? "yes" : "no");
}