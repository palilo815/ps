#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int v = 0, u, k; v < n; ++v) {
        for (cin >> k; k--;) {
            cin >> u, --u;
            adj[u].emplace_back(v);
        }
    }
    vector<int> dist(n);
    queue<int> q;
    auto solve = [&](int root) -> int {
        fill(dist.begin(), dist.end(), 0);
        dist[root] = 1;
        q.emplace(root);
        while (!q.empty()) {
            const auto u = q.front();
            q.pop();
            for (const auto& v : adj[u]) {
                if (!dist[v]) {
                    dist[v] = dist[u] + 1;
                    q.emplace(v);
                }
            }
        }
        if (all_of(dist.begin(), dist.end(), [&](const auto& x) { return x; })) {
            return accumulate(dist.begin(), dist.end(), 0);
        } else {
            return INT_MAX;
        }
    };
    int ans = INT_MAX;
    for (int i = 0; i < n; ++i) {
        chmin(ans, solve(i));
    }
    cout << ans;
}