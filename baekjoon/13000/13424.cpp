#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100;

vector<p> adj[max_N + 1];
int dist[max_N + 1];
int total[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        for (int i = 1; i <= N; ++i) adj[i].clear();
        while (M--) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }

        memset(total, 0, sizeof(total));
        int K; cin >> K;
        while (K--) {
            int src; cin >> src;
            fill(dist + 1, dist + N + 1, INT_MAX);
            dist[src] = 0;

            priority_queue<p, vector<p>, greater<p>> pq;
            pq.emplace(0, src);
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
            for (int i = 1; i <= N; ++i)
                total[i] += dist[i];
        }
        int d = INT_MAX, ans = -1;
        for (int i = 1; i <= N; ++i) if (total[i] < d)
            d = total[i], ans = i;
        cout << ans << '\n';    
    }
    return 0;
}