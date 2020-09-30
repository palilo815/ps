#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 2e3 + 1;
const int mxT = 1e2;

vector<pair<int, int>> adj[mxN];
int dist[mxN], dst[mxT];

void solve() {
    int N, M, T, s, g, h;
    cin >> N >> M >> T >> s >> g >> h;

    for (int i = 1; i <= N; ++i)
        adj[i].clear();

    for (int u, v, w; M--;) {
        cin >> u >> v >> w;
        w <<= 1;
        if (u == g && v == h || u == h && v == g) --w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    memset(dist + 1, 0x3e, sizeof(int) * N);

    priority_queue<elem> pq;
    pq.emplace(dist[s] = 0, s);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        for (auto& [v, w] : adj[u])
            if (dist[v] > d + w)
                pq.emplace(dist[v] = d + w, v);
    }

    for (int i = 0; i < T; ++i)
        cin >> dst[i];

    sort(dst, dst + T);

    T = remove_if(dst, dst + T, [&](int& x) { return (dist[x] & 1) == 0; }) - dst;
    for (int i = 0; i < T; ++i)
        cout << dst[i] << ' ';
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}