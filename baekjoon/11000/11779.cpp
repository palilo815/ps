#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e3 + 1;

vector<pair<int, int>> adj[mxN];
int dist[mxN], par[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    int src, dst;
    cin >> src >> dst;

    memset(dist + 1, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[src] = 0, src);

    for (;;) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] != d) continue;
        if (u == dst) break;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w) {
                pq.emplace(dist[v] = d + w, v);
                par[v] = u;
            }
    }

    vector<int> path;
    for (int v = dst; v; v = par[v])
        path.emplace_back(v);

    cout << dist[dst] << '\n'
         << path.size() << '\n';
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        cout << *it << ' ';
    return 0;
}