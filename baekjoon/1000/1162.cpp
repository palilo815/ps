#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> p;
typedef tuple<ll, int, int> tup;

const int max_N = 10000;
const int max_K = 20;

vector<p> adj[max_N + 1];
ll dist[max_N + 1][max_K + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K; cin >> N >> M >> K;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    for (int i = 1; i <= N; ++i) for (int j = 0; j <= K; ++j)
        dist[i][j] = INT64_MAX;
    dist[1][0] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, 1);
    while (1) {
        auto [d, k, u] = pq.top(); pq.pop();
        if (u == N) { cout << d; break; }

        for (auto [w, v] : adj[u]) {
            if (dist[v][k] > d + w) {
                dist[v][k] = d + w;
                pq.emplace(d + w, k, v);
            }
            if (k < K && dist[v][k + 1] > d) {
                dist[v][k + 1] = d;
                pq.emplace(d, k + 1, v);
            }
        }
    }
    return 0;
}