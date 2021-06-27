#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;

    int mn = -3 * (n - k), mx = 3 * (n - k);

    int rated = 0;
    for (int x; k--;) {
        cin >> x;
        rated += x;
    }
    mn += rated, mx += rated;

    cout << fixed << setprecision(9)
         << double(mn) / n << ' ' << double(mx) / n;
}