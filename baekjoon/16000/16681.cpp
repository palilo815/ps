#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct elem {
    ll d;
    int u;
    elem(ll d, int u) : d(d), u(u) {}
    bool operator <(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e5 + 1;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int h[mxN];
vector<pair<int, int>> adj[mxN];
ll up[mxN], dw[mxN];

void dijk(ll dist[], int src) {
    priority_queue<elem> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto& [w, v] : adj[u]) {
            ll D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, D, E;
    cin >> N >> M >> D >> E;
    for (int i = 1; i <= N; ++i)
        cin >> h[i];
    for (int u, v, w; M; --M) {
        cin >> u >> v >> w;
        if (h[u] < h[v]) adj[u].emplace_back(w, v);
        else if (h[u] > h[v]) adj[v].emplace_back(w, u);
    }

    memset(up + 1, 0x3f, sizeof(ll) * N);
    memset(dw + 1, 0x3f, sizeof(ll) * N);

    dijk(up, 1);
    dijk(dw, N);

    ll ans = INT64_MIN;
    for (int i = 2; i < N; ++i) {
        if (up[i] == INF || dw[i] == INF) continue;
        ans = max(ans, h[i] * E - D * (up[i] + dw[i]));
    }

    if (ans == INT64_MIN) cout << "Impossible";
    else cout << ans;
    return 0;
}