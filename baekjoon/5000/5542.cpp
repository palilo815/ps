#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int MAX = 100000;

int N, M, K, Q;
vector<p> adj[MAX];
p edge[MAX << 1];
int dist[MAX];
int parent[MAX];

p q[MAX];
int lo[MAX], hi[MAX];
vector<int> vt[MAX << 1];

int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u ^ v) parent[u] = v;
}
void Dijkstra() {
    memset(dist, 0x3f, sizeof(int) * N);
    priority_queue<p, vector<p>, greater<p>> pq;

    while (K--) {
        int s; cin >> s;
        --s;
        pq.emplace(dist[s] = 0, s);
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto& [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
}
bool go() {
    memset(parent, -1, sizeof(int) * N);
    loop(i, M) vt[i].clear();

    bool ret = false;
    loop(i, Q) if (lo[i] ^ hi[i]) {
        vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
        ret = true;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M >> K >> Q;
    loop(i, M) {
        int u, v, w; cin >> u >> v >> w;
        edge[i] = {--u, --v};
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    Dijkstra();
    sort(edge, edge + M, [](p & a, p & b) -> bool {
        return min(dist[a.first], dist[a.second]) > min(dist[b.first], dist[b.second]);
    });

    loop(i, Q) {
        cin >> q[i].first >> q[i].second;
        --q[i].first, --q[i].second;
    }

    fill(hi, hi + Q, M);
    while (go()) loop(m, M) {
        _union(edge[m].first, edge[m].second);
        for (int& i : vt[m]) {
            int u = _find(q[i].first), v = _find(q[i].second);
            u == v ? (hi[i] = m) : (lo[i] = m + 1);
        }
    }
    loop(i, Q) cout << min(dist[edge[lo[i]].first], dist[edge[lo[i]].second]) << '\n';
    return 0;
}