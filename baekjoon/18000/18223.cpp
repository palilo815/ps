#include <bits/stdc++.h>
using namespace std;

const int mxV = 5e3;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

vector<pair<int, int>> adj[mxV + 1];
int dist[mxV + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int V, E, P;
    cin >> V >> E >> P;

    for (int u, v, w; E--;) {
        cin >> u >> v >> w;
        w <<= 1;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    for (auto& [w, v] : adj[P])
        --w;

    memset(dist + 1, 0x3f, sizeof(int) * V);

    priority_queue<elem> pq;
    pq.emplace(dist[1] = 0, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto& [w, v] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }
    cout << (dist[V] & 1 ? "SAVE HIM" : "GOOD BYE");
}