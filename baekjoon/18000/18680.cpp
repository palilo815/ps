#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> dist(n);
    auto bfs = [&](int src) {
        fill(dist.begin(), dist.end(), -1);
        dist[src] = 0;

        queue<int> q;
        q.emplace(src);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& v : adj[u])
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.emplace(v);
                }
        }
        return max_element(dist.begin(), dist.end());
    };

    cout << n - 1 - *bfs(bfs(0) - dist.begin()) << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}