#include <bits/stdc++.h>
using namespace std;

struct edge {
    int c, t, u;
    edge(int _c, int _t, int _u) : c(_c), t(_t), u(_u) {}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, f;
    cin >> n >> m >> f;

    vector<vector<edge>> adj(n);
    for (int u, v, c, t; m--;) {
        cin >> u >> v >> c >> t, --u, --v;
        adj[u].emplace_back(c, t, v);
        adj[v].emplace_back(c, t, u);
    }

    vector<int64_t> rate(n);
    vector<int> cost(n), time(n);
    vector<bool> visited(n);
    auto solve = [&](int64_t p, int64_t h) {
        fill(rate.begin(), rate.end(), 0x3f3f3f3f3f3f3f3f);
        fill(visited.begin(), visited.end(), false);

        int64_t profit = f, hour = 0;
        for (int cnt = n; cnt--;) {
            int u = -1;
            for (int i = 0; i < n; ++i)
                if (!visited[i] && (u == -1 || rate[i] < rate[u]))
                    u = i;

            visited[u] = true;
            profit -= cost[u], hour += time[u];

            for (const auto& [c, t, v] : adj[u])
                if (!visited[v] && rate[v] > c * h + t * p) {
                    rate[v] = c * h + t * p;
                    cost[v] = c, time[v] = t;
                }
        }
        return make_pair(profit, hour);
    };

    int64_t profit = 0, hour = 1;
    for (;;) {
        auto [p, h] = solve(profit, hour);
        if (p <= 0 || profit == p && hour == h) break;
        profit = p, hour = h;
    }
    cout << fixed << setprecision(4) << double(profit) / hour;
}