#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using p = pair<int, int>;
using tup = tuple<int, int, int>;

const int max_N = 1000;

vector<tup> adj[max_N + 1];
int cost[max_N + 1];
int flow[max_N];

int Dijkstra(int N, int limit) {
    memset(cost + 1, 0x3f, sizeof(int)*N);
    cost[1] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 1);

    while (!pq.empty()) {
        auto [c, u] = pq.top(); pq.pop();
        if (cost[u] < c) continue;
        if (u == N) return c;

        for (auto [w1, w2, v] : adj[u])
            if (w2 >= limit && c + w1 < cost[v]) {
                cost[v] = c + w1;
                pq.emplace(cost[v], v);
            }
    }
    return -1;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v, c, f; cin >> u >> v >> c >> f;
        adj[u].emplace_back(c, f, v);
        adj[v].emplace_back(c, f, u);
        flow[i] = f;
    }

    sort(flow, flow + M);
    M = unique(flow, flow + M) - flow;

    ll best_c = 1, best_f = 0;
    for (int i = 0; i < M; ++i) {
        ll f = flow[i];
        ll c = Dijkstra(N, f);
        if (c != -1 && f * best_c > c * best_f)
            best_c = c, best_f = f;
    }
    cout << 1000000 * best_f / best_c;
    return 0;
}