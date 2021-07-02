#include <bits/stdc++.h>
using namespace std;

constexpr int MX_N = 21;

int adj[MX_N], dist[1 << MX_N], prv[1 << MX_N];
char shot[1 << MX_N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

TOP:;
    int n, m;
    cin >> n >> m;
    if (!n && !m) return 0;

    memset(adj, 0, sizeof(int) * n);
    for (int u, v; m--;) {
        cin >> u >> v;
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
    }

    const int full = (1 << n) - 1;

    memset(dist, -1, sizeof(int) * (1 << n));
    dist[full] = 0;

    queue<int> q;
    q.emplace(full);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (int i = 0; i < n; ++i)
            if (u >> i & 1) {
                int v = 0;
                for (int j = 0, u2 = u ^ (1 << i); j < n; ++j)
                    if (u2 >> j & 1)
                        v |= adj[j];

                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    shot[v] = i;
                    prv[v] = u;
                    q.emplace(v);
                }
            }
    }

    if (~dist[0]) {
        vector<int> trace;
        for (int i = 0; i != full; i = prv[i])
            trace.emplace_back(int(shot[i]));
        reverse(trace.begin(), trace.end());

        cout << trace.size() << ':';
        for (const auto& x : trace)
            cout << ' ' << x;
        cout << '\n';
    } else {
        cout << "Impossible\n";
    }
    goto TOP;
}