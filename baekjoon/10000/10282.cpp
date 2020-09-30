#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e4 + 1;
const int INF = 0x3f3f3f3f;

vector<elem> adj[mxN];
int dist[mxN];

void solve() {
    int N, M, s;
    cin >> N >> M >> s;

    for (int i = 1; i <= N; ++i)
        adj[i].clear();

    for (int u, v, w; M--;) {
        cin >> v >> u >> w;
        adj[u].emplace_back(v, w);
    }

    memset(dist + 1, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[s] = 0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d) continue;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }
    cout << count_if(dist + 1, dist + N + 1, [&](int& x) { return x == INF ? (x = 0) : 1; }) << ' '
         << *max_element(dist + 1, dist + N + 1) << '\n';
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