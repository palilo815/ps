#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto b(a);
    sort(b.begin(), b.end());
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) continue;
        const auto j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        const auto g = gcd(a[i], a[j]);
        const auto x = a[i] / g, y = a[j] / g;
        auto parametric = [&]<typename T>(T lo, T hi, T key) {
            auto f = [&](T mid) -> bool {
                return mid * mid >= key;
            };
            // first true
            while (lo != hi) {
                auto mid = lo + (hi - lo) / 2;
                f(mid) ? hi = mid : lo = mid + 1;
            }
            return lo;
        };
        auto ra = parametric(static_cast<int64_t>(1), static_cast<int64_t>(sqrt(x + 1)), x);
        auto rb = parametric(static_cast<int64_t>(1), static_cast<int64_t>(sqrt(y + 1)), y);
        if (ra * ra != a[i] / g || rb * rb != a[j] / g) return cout << "NO", 0;
    }
    cout << "YES";
}
