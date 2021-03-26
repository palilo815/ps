#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    constexpr int INF = 0x3f3f3f3f;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int u, v; m--;) {
        cin >> u >> v, --u, --v;
        dist[u][v] = dist[v][u] = 1;
    }

    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            if (dist[i][k] != INF)
                for (int j = 0; j < n; ++j)
                    if (dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

    int a0, a1, mn = INT_MAX;
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < n; ++k)
                sum += min(dist[i][k], dist[j][k]);
            if ((sum <<= 1) < mn)
                mn = sum, a0 = i + 1, a1 = j + 1;
        }
    cout << a0 << ' ' << a1 << ' ' << mn;
}