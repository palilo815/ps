#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 10000;

vector<p> adj[max_N + 1];
int dist[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M, src; cin >> N >> M >> src;
        fill(dist, dist + N + 1, INT_MAX);
        for (int i = 1; i <= N; ++i) adj[i].clear();
        while (M--) {
            int v, u, w; cin >> v >> u >> w;
            adj[u].push_back({ w,v });
        }

        priority_queue<p, vector<p>, greater<p>> pq;
        pq.push({ 0,src });
        dist[src] = 0;

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (dist[u] < d) continue;

            for (auto [w, v] : adj[u]) {
                int D = d + w;
                if (dist[v] > D) {
                    dist[v] = D;
                    pq.push({ D,v });
                }
            }
        }

        int ans = 0, cnt = 0;
        for (int i = 1; i <= N; ++i) if (dist[i] != INT_MAX) {
            ++cnt;
            ans = max(ans, dist[i]);
        }
        cout << cnt << ' ' << ans << '\n';
    }
    return 0;
}