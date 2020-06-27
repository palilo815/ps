#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
using p = pair<unsigned, int>;
using ull = unsigned long long;

const int max_N = 20001;
const int max_K = 200;

vector<p> adj[max_N];
vector<p> rev[max_N];
int N, K;
int hub[max_K];
unsigned from[max_K][max_N];
unsigned to[max_K][max_N];
priority_queue<p, vector<p>, greater<p>> pq;

void Dijkstra(int src, vector<p> adj[], unsigned dist[]) {
    memset(dist + 1, 0xff, sizeof(int) * N);
    dist[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        for (auto [w, v] : adj[u]) {
            auto D = d + w;
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

    int M, Q; cin >> N >> M >> K >> Q;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        rev[v].emplace_back(w, u);
    }
    loop(i, K) cin >> hub[i];
    sort(hub, hub + K);

    loop(i, K) Dijkstra(hub[i], adj, from[i]);
    loop(i, K) Dijkstra(hub[i], rev, to[i]);

    int cnt = 0;
    ull ans = 0;
    while (Q--) {
        int u, v; cin >> u >> v;
        unsigned d = UINT_MAX;
        loop(i, K) if (to[i][u] != UINT_MAX && from[i][v] != UINT_MAX)
            d = min(d, to[i][u] + from[i][v]);
        if (d != UINT_MAX) {
            ++cnt;
            ans += d;
        }
    }
    cout << cnt << '\n' << ans;
    return 0;
}