#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef struct {
    int u, v, w;
} edge;

const int max_N = 100000;
const int max_M = 200000;

vector<pii> adj[max_N];
edge road[max_M];

pli repair[max_M];
ll dist[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, C; cin >> N >> M >> C;
    ll total = 0;
    for (int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v, total += w;
        road[i].u = u, road[i].v = v, road[i].w = w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(dist, 0x3f, sizeof(ll) * N);
    dist[0] = 0;

    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [w, v] : adj[u]) {
            ll D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        repair[i].first = max(dist[road[i].u], dist[road[i].v]);
        repair[i].second = road[i].w;
    }
    sort(repair, repair + M);

    ll ans = total;
    for (int i = 0; i < M; ++i) {
        total -= repair[i].second;
        ans = min(ans, C * repair[i].first + total);
    }
    cout << ans;
    return 0;
}