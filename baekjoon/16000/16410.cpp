#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int x, y, x1, y1, x2, y2;
    cin >> x >> y >> x1 >> y1 >> x2 >> y2;

    double ans;
    if (x1 <= x && x <= x2) {
        ans = min(abs(y - y1), abs(y - y2));
    } else if (y1 <= y && y <= y2) {
        ans = min(abs(x - x1), abs(x - x2));
    } else {
        ans = min({hypot(x - x1, y - y1), hypot(x - x2, y - y1), hypot(x - x1, y - y2), hypot(x - x2, y - y2)});
    }

    cout << fixed << setprecision(9)
         << ans;
}