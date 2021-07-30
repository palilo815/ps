#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int u = 0, v; u < n; ++u) {
        for (;;) {
            cin >> v;
            if (!v) {
                break;
            }
            adj[u].emplace_back(v - 1);
        }
    }
    vector<int> cnt(n), dist(n, -1);
    for (int i = 0; i < n; ++i) {
        cnt[i] = (adj[i].size() + 1) >> 1;
    }
    int m;
    cin >> m;
    queue<int> q;
    for (int s; m--;) {
        cin >> s, --s;
        q.emplace(s);
        dist[s] = 0;
    }
    while (!q.empty()) {
        const auto u = q.front();
        q.pop();
        for (const auto& v : adj[u]) {
            if (dist[v] == -1 && --cnt[v] == 0) {
                dist[v] = dist[u] + 1;
                q.emplace(v);
            }
        }
    }
    for (const auto& x : dist) {
        cout << x << ' ';
    }
}