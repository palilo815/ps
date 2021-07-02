#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

constexpr int MX_N = 50000;

double x[MX_N], y[MX_N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

TOP:;
    int n;
    cin >> n;
    if (!n) return 0;

    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];

    auto range = minmax_element(x, x + n);

    auto f = [&](double mid) -> double {
        double ret = 0;
        for (int i = 0; i < n; ++i)
            chmax(ret, ((mid - x[i]) * (mid - x[i]) + y[i] * y[i]));
        return ret;
    };

    double lo = *range.first, hi = *range.second;

    while (hi - lo > 1e-5) {
        auto mid1 = lo + (hi - lo) / 3;
        auto mid2 = hi - (hi - lo) / 3;

        auto f1 = f(mid1), f2 = f(mid2);
        (f1 < f2 ? hi = mid2 : lo = mid1);
    }

    auto mid = (lo + hi) / 2;
    cout << fixed << setprecision(9)
         << mid << ' ' << sqrt(f(mid)) << '\n';
    goto TOP;
}