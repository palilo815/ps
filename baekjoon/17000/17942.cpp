#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef pair<int, int> p;

const int MAX = 100001;

int dist[MAX];
bool solve[MAX];
vector<p> adj[MAX];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    LOOP(i, N) cin >> dist[i];

    priority_queue<p, vector<p>, greater<p>> pq;
    LOOP(i, N) pq.emplace(dist[i], i);

    int K; cin >> K;
    while (K--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
    }

    while (1) {
        auto [d, u] = pq.top(); pq.pop();
        if (solve[u]) continue;
        if (--M == 0) {cout << d; break;}

        solve[u] = true;
        for (auto [w, v] : adj[u]) {
            dist[v] -= w;
            pq.emplace(dist[v], v);
        }
    }
    return 0;
}