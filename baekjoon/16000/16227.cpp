#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 1000;

int min_dist[max_N + 2];
int min_dust[max_N + 2];
vector<p> adj[max_N + 2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        if (w > 100) continue;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    memset(min_dist + 1, 0x3f, sizeof(int) * (N + 1));
    memset(min_dust + 1, 0x3f, sizeof(int) * (N + 1));

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, 0);

    while (1) {
        auto [d, dust, u] = pq.top(); pq.pop();
        if (min_dist[u] < d && min_dust[u] < dust) continue;
        if (u == N + 1) { cout << d; break; }

        if (dust) pq.emplace(d + 5, 0, u);
        for (auto [w, v] : adj[u]) {
            int D = d + w, DUST = dust + w;
            if (DUST > 100) continue;

            int flag = 0;
            if (min_dist[v] > D) min_dist[v] = D, flag = 1;
            if (min_dust[v] > DUST) min_dust[v] = DUST, flag = 1;
            if (flag) pq.emplace(D, DUST, v);
        }
    }
    return 0;
}