#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;

const int max_N = 100000;
const int mod = 1000000009;

vector<pii> adj[max_N];
ll dist[max_N];
int cnt[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, src, dst; cin >> N >> M >> src >> dst;
    --src, --dst;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(dist, 0x3f, sizeof(ll) * N);
    dist[src] = 0;
    cnt[src] = 1;

    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (u == dst) break;

        for (auto [w, v] : adj[u]) {
            ll D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                cnt[v] = cnt[u];
                pq.emplace(D, v);
            }
            else if (dist[v] == D)
                cnt[v] = (cnt[v] + cnt[u]) % mod;
        }
    }
    cout << cnt[dst];
    return 0;
}