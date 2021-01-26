#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

struct sensor {
    int x, y, r;
};

sensor a[mxN];
double dist[mxN + 1];
bitset<mxN + 1> conn;

void solve() {
    conn.reset();
    int w, n;
    cin >> w >> n;

    for (int i = 0; i < n; ++i)
        cin >> a[i].x >> a[i].y >> a[i].r;

    for (int i = 0; i < n; ++i)
        dist[i] = a[i].x - a[i].r;
    dist[n] = w;

    for (double ans = 0;;) {
        int k = -1;
        for (int i = 0; i < n + 1; ++i)
            if (!conn[i] && (k == -1 || dist[i] < dist[k]))
                k = i;

        conn[k] = true;
        ans = max(ans, dist[k]);
        if (k == n) {
            cout << ans / 2 << '\n';
            return;
        }

        for (int i = 0; i < n; ++i)
            if (!conn[i])
                dist[i] = min(dist[i], hypot(a[k].x - a[i].x, a[k].y - a[i].y) - a[k].r - a[i].r);
        dist[n] = min(dist[n], double(w) - a[k].x - a[k].r);
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(9);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}