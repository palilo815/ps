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
    vector<int> src, in, out;
    for (int u, v, w1, w2; m--;) {
        cin >> u >> v >> w1 >> w2, --u, --v;
        if (!u || !v) {
            u ? swap(w1, w2) : swap(u, v);
            src.emplace_back(u);
            in.emplace_back(w1);
            out.emplace_back(w2);
        } else {
            adj[u].emplace_back(w1, v);
            adj[v].emplace_back(w2, u);
        }
    }

    vector<int> dist(n);
    priority_queue<elem> pq;
    int ans = INT_MAX;
    auto dijk = [&](int pos, bool flag) {
        fill(dist.begin(), dist.end(), INF);
        for (int i = 0; i < int(src.size()); ++i)
            if ((i >> pos & 1) == flag)
                pq.emplace(dist[src[i]] = in[i], src[i]);

        while (!pq.empty()) {
            const auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (const auto& [w, v] : adj[u])
                if (dist[v] > d + w)
                    pq.emplace(dist[v] = d + w, v);
        }

        for (int i = 0; i < int(src.size()); ++i)
            if ((i >> pos & 1) != flag)
                ans = min(ans, dist[src[i]] + out[i]);
    };

    for (int i = __lg(src.size() - 1); ~i; --i)
        dijk(i, false), dijk(i, true);
    cout << ans;
}