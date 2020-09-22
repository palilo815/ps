#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using p = pair<int, int>;
struct elem {
    ll d;
    int u;
    elem(ll d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e5;

vector<p> adj[mxN];
ll dist[mxN];
int par[mxN], sign[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    memset(dist, 0x3f, sizeof(ll) * N);
    memset(par, -1, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[1] = 0, 1);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d) continue;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w) {
                par[v] = u;
                pq.emplace(dist[v] = d + w, v);
            }
    }

    copy(par, par + N, sign);

    vector<bool> visited(N);
    visited[0] = true;

    queue<int> q;
    q.emplace(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto& [v, w] : adj[u])
            if (v ^ sign[u] && !visited[v]) {
                visited[v] = true, par[v] = u;
                q.emplace(v);
            }
    }
    if (!visited[1]) cout << "impossible";
    else {
        vector<int> path;
        for (int u = 1; u; u = par[u])
            path.emplace_back(u);
        path.emplace_back(0);

        cout << path.size();
        for (auto it = path.rbegin(); it != path.rend(); ++it)
            cout << ' ' << *it;
    }
    return 0;
}