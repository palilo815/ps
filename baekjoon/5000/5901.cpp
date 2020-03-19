#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 10000;
const int max_K = 5;

vector<p> adj[max_N + 1];
int market[max_K];
int order[max_K];
int dist[max_K][max_N + 1];
bool c[max_N + 1];

void Dijkstra(const int i) {
    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, market[i]);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[i][u] < d) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[i][v] > D) {
                dist[i][v] = D;
                pq.emplace(D, v);
            }
        }
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K; cin >> N >> M >> K;
    loop(i, K) {
        cin >> market[i];
        c[market[i]] = true;
    }
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    loop(i, K) {
        fill(dist[i] + 1, dist[i] + N + 1, INT_MAX);
        dist[i][market[i]] = 0;
        Dijkstra(i);
    }

    loop(i, K) order[i] = i;
    int ans = INT_MAX;
    do {
        int sum = INT_MAX;
        for (int i = 1; i <= N; ++i) if (!c[i])
            sum = min(sum, dist[order[0]][i] + dist[order[K - 1]][i]);
        loop(i, K - 1)
            sum += dist[order[i + 1]][market[order[i]]];
        ans = min(ans, sum);
    } while (next_permutation(order, order + K));
    cout << ans;
    return 0;
}