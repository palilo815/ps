#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 500;

int x[mxN], y[mxN];
double dist[mxN], ans[mxN];
bool conn[mxN];

void solve() {
    int S, N; cin >> S >> N;
    loop(i, N) cin >> x[i] >> y[i];

    fill(dist, dist + N, DBL_MAX);
    dist[0] = 0;

    memset(conn, 0, N);

    int cnt = N;
    loop(j, N) {
        int k = -1;
        loop(i, N) if (!conn[i] && (k == -1 || dist[i] < dist[k]))
            k = i;

        ans[j] = dist[k];
        conn[k] = true;

        loop(i, N) if (!conn[i]) {
            int dx = x[i] - x[k], dy = y[i] - y[k];
            double d = sqrt(dx * dx + dy * dy);
            if (dist[i] > d) dist[i] = d;
        }
    }

    sort(ans, ans + N);
    cout << fixed << setprecision(2)
         << ans[N - S] << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}