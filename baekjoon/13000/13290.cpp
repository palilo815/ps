#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 100;

int item[max_N + 1];
int dist[max_N + 1];
vector<p> adj[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) cin >> item[i];
    int M; cin >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(dist + 1, dist + N + 1, INT_MAX);
    dist[1] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, 1);
    int ans = -1;
    while (!pq.empty()) {
        auto [d, box, u] = pq.top(); pq.pop();
        box += item[u];
        if (u == N) {
            if (dist[u] < d) break;
            ans = max(ans, box);
        }
        if (dist[u] < d) continue;

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] >= D) {
                dist[v] = D;
                pq.emplace(D, box, v);
            }
        }
    }
    
    if (ans == -1) cout << "impossible";
    else cout << dist[N] << ' ' << ans;
    return 0;
}