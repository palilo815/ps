#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 5e2;
const int INF = 0x3f3f3f3f;

vector<pair<int, int>> adj[mxN];
vector<int> par[mxN];
int N, M, src, dst, dist[mxN];
bool visited[mxN];

void dijk() {
    memset(dist, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[src] = 0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w) {
                pq.emplace(dist[v] = d + w, v);
                par[v] = {u};
            } else if (dist[v] == d + w)
                par[v].emplace_back(u);
    }
}
void erase_edges() {
    memset(visited, 0, N);
    visited[dst] = true;

    queue<int> q;
    q.emplace(dst);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int& u : par[v]) {
            find_if(adj[u].begin(), adj[u].end(), [&](auto& e) {
                return e.first == v;
            })->second = INF;
            if (!visited[u]) {
                visited[u] = true;
                q.emplace(u);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (;;) {
        cin >> N >> M;
        if (!N) break;

        for (int i = 0; i < N; ++i)
            adj[i].clear();
        for (int i = 0; i < N; ++i)
            par[i].clear();

        cin >> src >> dst;
        for (int u, v, w; M--;) {
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
        }

        dijk();
        erase_edges();
        dijk();

        cout << (dist[dst] == INF ? -1 : dist[dst]) << '\n';
    }
    return 0;
}