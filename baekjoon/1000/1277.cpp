#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct elem {
    double d;
    int u;
    elem(double d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e3;

int x[mxN], y[mxN];
double adj[mxN][mxN], dist[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, W;
    double M;
    cin >> N >> W >> M;
    M += 1e-6;

    loop(i, N) cin >> x[i] >> y[i];
    loop(j, N) loop(i, j) {
        long long dx = x[i] - x[j], dy = y[i] - y[j];
        double d = sqrt(dx * dx + dy * dy);
        adj[i][j] = adj[j][i] = d > M ? DBL_MAX : d;
    }

    for (int u, v; W--;) {
        cin >> u >> v;
        --u, --v;
        adj[u][v] = adj[v][u] = 0;
    }

    fill(dist + 1, dist + N, DBL_MAX);

    priority_queue<elem> pq;
    pq.emplace(0, 0);

    for (;;) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] < d) continue;
        if (u == N - 1) return cout << (int)(d * 1000), 0;

        loop(v, N) if (adj[u][v] != DBL_MAX && dist[v] > d + adj[u][v])
            pq.emplace(dist[v] = d + adj[u][v], v);
    }
}