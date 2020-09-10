#include <bits/stdc++.h>
#define sum(i) (d1[i]+d2[i])
using namespace std;
using p = pair<int, int>;

const int mxV = 101;

vector<p> adj[mxV];
int d1[mxV], d2[mxV];

void dijkstra(int src, int dist[]) {
    dist[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto& [w, v] : adj[u])
            if (dist[v] > dist[u] + w)
                pq.emplace(dist[v] = dist[u] + w, v);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int V, E; cin >> V >> E;
    for (int u, v, w; E--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    int s1, s2; cin >> s1 >> s2;
    memset(d1 + 1, 0x3f, sizeof(int) * V);
    memset(d2 + 1, 0x3f, sizeof(int) * V);

    dijkstra(s1, d1);
    dijkstra(s2, d2);

    vector<int> ans;
    int mn = INT_MAX;
    for (int i = 1; i <= V; ++i)
        if (i ^ s1 && i ^ s2) {
            if (sum(i) < mn) {
                mn = sum(i);
                ans = {i};
            }
            else if (sum(i) == mn)
                ans.emplace_back(i);
        }

    ans.erase(remove_if(ans.begin(), ans.end(), [&](int& i) {
        return d1[i] > d2[i];
    }), ans.end());

    auto it = min_element(ans.begin(), ans.end(), [&](int& a, int& b) {
        return d1[a] == d1[b] ? a < b : d1[a] < d1[b];
    });

    cout << (it == ans.end() ? -1 : *it);
    return 0;
}