#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, l;
    cin >> n >> l;

    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    double lo = 0, hi = sqrt(5e18);
    while (hi - lo > 1e-4) {
        double mid = (lo + hi) / 2, ed = 0;
        for (const auto& [x, y] : a) {
            double dx = sqrt(mid * mid - double(y) * y);
            if (x - dx <= ed) chmax(ed, x + dx);
        }
        (ed < l ? lo : hi) = mid;
    }

    cout << fixed << setprecision(9)
         << (lo + hi) / 2;
}