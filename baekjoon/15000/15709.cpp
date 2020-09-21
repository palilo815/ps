#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using p = pair<int, int>;
struct elem {
    ll d;
    int u;
    elem(ll d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mx = 20100;
const ll oo = 0x3f3f3f3f3f3f3f3f;

vector<p> adj[mx];
ll dist[mx][100];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, B, K, Q;
    cin >> N >> M >> B >> K >> Q;

    for (int u, v, w; K--;) {
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    memset(dist, 0x3f, sizeof(dist));

    priority_queue<elem> pq;
    for (int i = 0; i < B; ++i) {
        pq.emplace(dist[N + M + i][i] = 0, N + M + i);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (dist[u][i] < d) continue;

            for (auto& [v, w] : adj[u])
                if (dist[v][i] > dist[u][i] + w)
                    pq.emplace(dist[v][i] = dist[u][i] + w, v);
        }
    }

    for (int u, v; Q--;) {
        cin >> u >> v;
        --u, --v;
        ll ans = oo;

        for (int i = 0; i < B; ++i)
            ans = min(ans, dist[u][i] + dist[v][i]);
        cout << (ans == oo ? -1 : ans) << '\n';
    }
    return 0;
}