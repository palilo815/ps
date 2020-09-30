#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u, speed;
    elem(int d, int u, int speed) : d(d), u(u), speed(speed) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 4e3 + 1;

int dist[mxN][3];
vector<pair<int, int>> adj[mxN];

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

    memset(dist[1], 0x3f, sizeof(int) * 3 * N);

    priority_queue<elem> pq;
    pq.emplace(dist[1][0] = 0, 1, 0), pq.emplace(dist[1][1] = 0, 1, 1);

    while (!pq.empty()) {
        auto [d, u, speed] = pq.top();
        pq.pop();
        if (d != dist[u][speed]) continue;

        for (auto& [v, w] : adj[u])
            if (dist[v][2 - speed] > d + (w << speed))
                pq.emplace(dist[v][2 - speed] = d + (w << speed), v, 2 - speed);
    }

    cout << count_if(dist + 1, dist + N + 1, [&](auto& it) {
        return it[1] < it[0] && it[1] < it[2];
    });
    return 0;
}