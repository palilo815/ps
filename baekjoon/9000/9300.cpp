#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    double h, angle;
    for (int TC = 1; TC <= T; ++TC) {
        cin >> h >> angle;
        cout << "Case " << TC << ": ";
        if (angle == 0) {
            cout << "Infinity\n";
        } else {
            const auto t = tan(angle * M_PI / 180.0);
            cout << fixed << setprecision(9) << fabs(h / t - h) << '\n';
        }
    }
}