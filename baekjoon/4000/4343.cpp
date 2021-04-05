#include <bits/stdc++.h>
using namespace std;

void solve() {
    int s, n;
    cin >> s >> n;

    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    vector<double> dist(n, DBL_MAX);
    dist[0] = 0;

    vector<bool> con(n);
    for (int t = n; t--;) {
        int k = -1;
        for (int i = 0; i < n; ++i)
            if (!con[i] && (k == -1 || dist[i] < dist[k]))
                k = i;

        assert(~k);
        con[k] = true;

        for (int i = 0; i < n; ++i)
            if (!con[i])
                dist[i] = min(dist[i], hypot(a[i].first - a[k].first, a[i].second - a[k].second));
    }

    nth_element(dist.begin(), dist.end() - s, dist.end());
    cout << fixed << setprecision(2)
         << dist.end()[-s] << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}