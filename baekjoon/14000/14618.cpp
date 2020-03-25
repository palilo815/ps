#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 5000;
const int A = 1;
const int B = -1;

vector<p> adj[max_N + 1];
int dist[max_N + 1];
int house[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, src, K;
    cin >> N >> M >> src >> K;
    for (int i = 0; i < K; ++i) {
        int a; cin >> a;
        house[a] = A;
    }
    for (int i = 0; i < K; ++i) {
        int b; cin >> b;
        house[b] = B;
    }

    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(dist + 1, dist + N + 1, INT_MAX);
    dist[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);

    char ans = '\0';
    int ans_d = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        if (house[u]) {
            if (ans && ans_d < d) break;
            ans_d = d;
            ans = (house[u] == A ? 'A' : 'B');
            if (ans == 'A') break;
        }

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }
    if (ans) cout << ans << '\n' << ans_d;
    else cout << -1;
    return 0;
}