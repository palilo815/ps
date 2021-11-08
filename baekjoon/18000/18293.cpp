#include <bits/stdc++.h>
using namespace std;

struct min_heap_elem {
    int c, d, u;
    min_heap_elem(int c, int d, int u) : c(c), d(d), u(u) {}
    bool operator<(const min_heap_elem& rhs) const {
        return c > rhs.c;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    pair<int, int> s, t;
    int b, c0, m;
    cin >> s.first >> s.second >> t.first >> t.second >> b >> c0 >> m;
    vector<int> co2(m);
    for (auto& x : co2) {
        cin >> x;
    }
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    vector<vector<pair<int, int>>> adj(n);
    for (int u = 0, m, w, v; u < n; ++u) {
        cin >> a[u].first >> a[u].second;
        for (cin >> m; m--;) {
            cin >> v >> w, --w;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }
    }
    const auto get_dist = [&](const pair<int, int>& u, const pair<int, int>& v) {
        const auto dx2 = (u.first - v.first) * (u.first - v.first);
        const auto dy2 = (u.second - v.second) * (u.second - v.second);
        const int ret = sqrt(dx2 + dy2);
        return ret * ret < dx2 + dy2 ? ret + 1 : ret;
    };
    vector cost(n, vector(b + 1, INF));
    priority_queue<min_heap_elem> pq;
    for (int i = 0; i < n; ++i) {
        const auto d = get_dist(s, a[i]);
        if (d <= b) {
            pq.emplace(cost[i][d] = c0 * d, d, i);
        }
    }
    if (const auto d = get_dist(s, t);
        d <= b) {
        pq.emplace(c0 * d, d, n);
    }
    while (!pq.empty()) {
        const auto [c, d, u] = pq.top();
        pq.pop();
        if (u == n) return cout << c, 0;
        if (cost[u][d] != c) continue;
        for (const auto& [w, v] : adj[u]) {
            const auto dd = d + get_dist(a[u], a[v]),
                       cc = c + (dd - d) * co2[w];
            if (dd <= b && cost[v][dd] > cc) {
                pq.emplace(cost[v][dd] = cc, dd, v);
                for (int i = dd + 1; i <= b && cost[v][i] > cc; ++i) {
                    cost[v][i] = cc;
                }
            }
        }
        if (const auto dd = d + get_dist(t, a[u]);
            dd <= b) {
            pq.emplace(c + (dd - d) * c0, dd, n);
        }
    }
    cout << -1;
}