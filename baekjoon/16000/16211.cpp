#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 200000;

vector<p> adj[max_N + 1];
int d1[max_N + 1], d2[max_N + 1];

void Dijkstra(priority_queue<p, vector<p>, greater<p>>& pq, int dist[]) {
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K; cin >> N >> M >> K;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(d1 + 2, d1 + N + 1, INT_MAX);
    fill(d2 + 1, d2 + N + 1, INT_MAX);

    priority_queue<p, vector<p>, greater<p>> pq1;
    priority_queue<p, vector<p>, greater<p>> pq2;

    pq1.emplace(0, 1);
    while (K--) {
        int x; cin >> x;
        d2[x] = 0;
        pq2.emplace(0, x);
    }

    Dijkstra(pq1, d1);
    Dijkstra(pq2, d2);

    bool ans = false;
    for (int i = 2; i <= N; ++i)
        if (d1[i] < d2[i]) {
            cout << i << ' ';
            ans = true;
        }
    if (!ans) cout << 0;
    return 0;
}