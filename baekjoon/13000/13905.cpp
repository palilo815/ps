#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

vector<p> adj[max_N + 1];
int cnt[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, src, dst;
    cin >> N >> M >> src >> dst;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    cnt[src] = INT_MAX;

    priority_queue<p> pq;
    pq.emplace(INT_MAX, src);

    while (!pq.empty()) {
        auto [c, u] = pq.top(); pq.pop();
        if (cnt[u] > c) continue;
        if (u == dst) break;

        for (auto [w, v] : adj[u]) {
            int C = min(c, w);
            if (cnt[v] < C) {
                cnt[v] = C;
                pq.emplace(C, v);
            }
        }
    }
    cout << cnt[dst];
    return 0;
}