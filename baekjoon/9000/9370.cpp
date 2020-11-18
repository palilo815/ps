#include <bits/stdc++.h>
using namespace std;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

void solve() {
    int n, m, t, s, g, h;
    cin >> n >> m >> t >> s >> g >> h;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> dist(n + 1, 0x3e3e3e3e);

    for (int u, v, w; m--;) {
        cin >> u >> v >> w;
        w <<= 1;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    for (auto& [w, v] : adj[g])
        if (v == h) {
            --w;
            break;
        }
    for (auto& [w, v] : adj[h])
        if (v == g) {
            --w;
            break;
        }

    priority_queue<elem> pq;
    pq.emplace(dist[s] = 0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto& [w, v] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }

    vector<int> vt(t);
    for (auto& x : vt) cin >> x;

    sort(vt.begin(), vt.end());

    for (auto& x : vt)
        if (dist[x] & 1)
            cout << x << ' ';
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}