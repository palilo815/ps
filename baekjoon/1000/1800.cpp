#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int max_N = 1000;

vector<p> adj[max_N + 1];
int price[max_N + 1][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K; cin >> N >> M >> K;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    for (int i = 1; i <= N; ++i)
        memset(price[i], 0x3f, sizeof(price[i]));
    price[1][0] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, 1);

    int ans = -1;
    while (!pq.empty()) {
        auto [p, c, u] = pq.top(); pq.pop();
        if (u == N) { ans = p; break; }
        if (price[u][c] < p) continue;

        if (c < K) for (auto [w, v] : adj[u])
                if (price[v][c + 1] > p) {
                    price[v][c + 1] = p;
                    pq.emplace(p, c + 1, v);
                }
        for (auto [w, v] : adj[u]) {
            int P = max(w, p);
            if (price[v][c] > P) {
                price[v][c] = P;
                pq.emplace(P, c, v);
            }
        }
    }
    cout << ans;
    return 0;
}