#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, t;
    cin >> n >> t;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w, i = n - 1; i--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    // {# of edges, -sum of edges}
    vector<pair<int, int>> dist(n);

    vector<int> stk;
    auto dfs = [&](int s) {
        fill(dist.begin(), dist.end(), pair(-1, -1));
        dist[s] = {0, 0};

        stk.emplace_back(s);
        while (!stk.empty()) {
            const auto u = stk.back();
            stk.pop_back();

            for (const auto& [w, v] : adj[u])
                if (dist[v].first == -1) {
                    dist[v] = {dist[u].first + 1, dist[u].second - w};
                    stk.emplace_back(v);
                }
        }
    };

    dfs(0);
    dfs(max_element(dist.begin(), dist.end()) - dist.begin());

    auto cost = -(max_element(dist.begin(), dist.end())->second);
    cout << (cost + t - 1) / t;
}