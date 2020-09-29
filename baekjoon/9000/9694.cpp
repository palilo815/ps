#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 20;

vector<elem> adj[mxN];
int dist[mxN], par[mxN];

void find_path(int u) {
    if (~par[u]) find_path(par[u]);
    cout << ' ' << u;
}
void solve() {
    int M, N;
    cin >> M >> N;

    for (int i = 0; i < N; ++i)
        adj[i].clear();

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    memset(par, -1, sizeof(int) * N);
    memset(dist, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[0] = 0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d) continue;
        if (u == N - 1) break;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w) {
                pq.emplace(dist[v] = d + w, v);
                par[v] = u;
            }
    }

    if (dist[N - 1] == 0x3f3f3f3f)
        cout << " -1";
    else
        find_path(N - 1);
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
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ":";
        solve();
    }
    return 0;
}