#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    struct acb {
        unsigned a, c, b;
    };
    int n;
    cin >> n;
    vector<acb> vt(n);
    for (auto& [a, c, b] : vt) {
        cin >> a >> c >> b;
    }
    auto less_or_equal = [&]<typename T>(T mid) {
        // 홀짝만 판별하면 되므로 오버플로우 생겨도 상관 x
        return accumulate(vt.begin(), vt.end(), T(0), [&](const auto& acc, const auto& x) {
            return mid < x.a ? acc : (acc + (min(mid, x.c) - x.a) / x.b + 1);
        });
    };
    auto parametric = [&]<typename T>(T lo, T hi) {
        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            less_or_equal(mid)& 1 ? hi = mid : lo = mid + 1;
        }
        // // last true
        // while (lo != hi) {
        //     auto mid = hi - (hi - lo) / 2;
        //     f(mid) ? lo = mid : hi = mid - 1;
        // }
        return lo;
    };
    // INT_MAX = (1 << 31) - 1
    const auto res = parametric(0u, 1u << 31);
    if (res == (1u << 31)) {
        cout << "NOTHING";
    } else {
        cout << res << ' ' << less_or_equal(res) - less_or_equal(res - 1);
    }
}
