#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;

int x[mx], y[mx], dist[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, R, D, sx, sy;
    cin >> N >> R >> D >> sx >> sy;
    loop(i, N) cin >> x[i] >> y[i];

    R *= R;
    memset(dist, -1, sizeof(int) * N);

    queue<int> q;
    loop(i, N) {
        int dx = sx - x[i], dy = sy - y[i];
        if (dx * dx + dy * dy <= R) {
            q.emplace(i);
            dist[i] = 0;
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        loop(v, N) if (dist[v] == -1) {
            int dx = x[u] - x[v], dy = y[u] - y[v];
            if (dx * dx + dy * dy <= R) {
                q.emplace(v);
                dist[v] = dist[u] + 1;
            }
        }
    }

    double ans = 0;
    loop(i, N) if (~dist[i])
        ans += D / pow(2, dist[i]);
    cout << fixed << setprecision(2) << ans;
    return 0;
}