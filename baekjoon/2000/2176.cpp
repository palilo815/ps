#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

vector<p> adj[max_N + 1];
int dist[max_N + 1];
int path[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(dist + 1, dist + N + 1, INT_MAX);
    dist[2] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 2);

    stack<int> arrive;
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;
        arrive.emplace(u);

        for (auto [w, v] : adj[u]) {
            int D = d + w;
            if (dist[v] > D) {
                dist[v] = D;
                pq.emplace(D, v);
            }
        }
    }

    path[1] = 1;
    while (!arrive.empty() && arrive.top() != 1)
        arrive.pop();

    while (!arrive.empty()) {
        int u = arrive.top(); arrive.pop();
        for (auto [w, v] : adj[u])
            if (dist[v] < dist[u]) {
                path[v] += path[u];
            }
    }
    cout << path[2];
    return 0;
}