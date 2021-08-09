#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;
    sort(a.begin(), a.end());
    pair<double, double> dp {}, prev_y {};
    double prev_x = 0;
    for (auto it = a.begin(), jt = a.begin(); it != a.end(); it = jt) {
        for (++jt; jt != a.end() && it->first == jt->first; ++jt) {
            ;
        }
        if (it != a.begin()) {
            pair<double, double> nxt {
                max(dp.first + hypot(it->first - prev_x, it->second - prev_y.first),
                    dp.second + hypot(it->first - prev_x, it->second - prev_y.second)),
                max(dp.first + hypot(prev(jt)->first - prev_x, prev(jt)->second - prev_y.first),
                    dp.second + hypot(prev(jt)->first - prev_x, prev(jt)->second - prev_y.second))};
            dp = nxt;
        }
        prev_x = it->first;
        prev_y = {it->second, prev(jt)->second};
    }
    cout << fixed << setprecision(9) << max(dp.first, dp.second);
}