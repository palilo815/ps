#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;

const int max_N = 1000;

vector<P> adj[max_N + 1];
priority_queue<int> dist[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, k; cin >> N >> M >> k;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
    }
    
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.emplace(0, 1);
    dist[1].emplace(0);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u].top()) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v].size() < k) {
                dist[v].emplace(D);
                pq.emplace(D, v);
            }
            else if (dist[v].top() > D) {
                dist[v].pop();
                dist[v].emplace(D);
                pq.emplace(D, v);
            }
        }
    }

    for (int i = 1; i <= N; ++i)
        cout << ((dist[i].size() == k) ? dist[i].top() : -1) << '\n';
    return 0;
}