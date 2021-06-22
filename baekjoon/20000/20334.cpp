#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

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
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m, p, g;
    cin >> n >> m >> p >> g;

    vector<int> family(p);
    for (auto& x : family) cin >> x, --x;

    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    auto dijk = [&](int s, vector<int>& dist) {
        priority_queue<elem> pq;
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

    vector rev_dist(n, INF);
    dijk(0, rev_dist);

    vector dist(p, vector<int>(n, INF));
    for (int i = 0; i < p; ++i)
        dijk(family[i], dist[i]);

    int64_t ans = LLONG_MAX;
    for (int i = 0; i < n; ++i) {
        int64_t sum = 0;
        for (const auto& d : dist)
            sum += (d[0] > d[i] + g && d[i] + rev_dist[i] == d[0]) ? d[i] + g : d[0];
        chmin(ans, sum);
    }
    cout << ans;
}