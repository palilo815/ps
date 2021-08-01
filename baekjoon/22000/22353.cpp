#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    double a, d, k;
    cin >> a >> d >> k;
    double ans = 0, lose_all_prev = 1;
    for (int i = 1;; ++i) {
        double win = d / 100.0;
        ans += i * win * lose_all_prev;
        if (d == 100.0) {
            break;
        }
        d = min(100.0, d + d * k / 100);
        lose_all_prev *= (1 - win);
    }
    cout << fixed << setprecision(7) << ans * a;
}