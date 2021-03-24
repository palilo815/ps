#include <bits/stdc++.h>
using namespace std;

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

    int x, y;

    cin >> m >> x;
    vector<int> mc(m);
    for (auto& i : mc) cin >> i, --i;

    cin >> m >> y;
    vector<int> st(m);
    for (auto& i : st) cin >> i, --i;

    vector<bool> town(n, true);
    for (const auto& i : mc) town[i] = false;
    for (const auto& i : st) town[i] = false;

    auto dijk = [&](vector<int>& src, vector<int>& dist) {
        struct elem {
            int d, u;
            elem(int d, int u) : d(d), u(u) {}
            bool operator<(const elem& rhs) const {
                return d > rhs.d;
            }
        };

        priority_queue<elem> pq;
        for (const auto& s : src)
            pq.emplace(dist[s] = 0, s);

        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (const auto& [w, v] : adj[u])
                if (dist[v] > d + w)
                    pq.emplace(dist[v] = d + w, v);
        }
    };

    vector<int> d0(n, 0x3f3f3f3f), d1(n, 0x3f3f3f3f);
    dijk(mc, d0);
    dijk(st, d1);

    int ans = INT_MAX;
    for (int i = 0; i < n; ++i)
        if (town[i] && d0[i] <= x && d1[i] <= y)
            ans = min(ans, d0[i] + d1[i]);
    cout << (ans == INT_MAX ? -1 : ans);
}