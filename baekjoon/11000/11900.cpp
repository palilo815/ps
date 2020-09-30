#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 2e3;

int a[mxN], dist[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 1; i < N; ++i)
        cin >> a[i];

    memset(dist, 0x3f, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[0] = 0, 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        for (int v = 1; v < u; ++v)
            if (a[N + v - u] && dist[v] > d + a[N + v - u])
                pq.emplace(dist[v] = d + a[N + v - u], v);
        for (int v = u + 1; v < N; ++v)
            if (a[v - u] && dist[v] > d + a[v - u])
                pq.emplace(dist[v] = d + a[v - u], v);
    }

    int Q;
    cin >> Q;
    for (int u, v; Q--;) {
        cin >> u >> v;
        int d = (u > v ? dist[u - v] : dist[N - (v - u)]);
        cout << (d == 0x3f3f3f3f ? -1 : d) << '\n';
    }
    return 0;
}