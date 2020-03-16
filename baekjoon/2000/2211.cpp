#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

vector<p> adj[max_N + 1];
int dist[max_N + 1];
bool connected[max_N + 1];
vector<p> path;

void find_path(int u) {
    connected[u] = true;
    for(auto [w,v] : adj[u]) if(!connected[v])
        if (dist[u] + w == dist[v]) {
            path.emplace_back(u, v);
            find_path(v);
        }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    fill(dist + 2, dist + N + 1, INT_MAX);

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 1);

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

    find_path(1);

    cout << path.size();
    for (auto [u, v] : path)
        cout << '\n' << u << ' ' << v;
    return 0;
}