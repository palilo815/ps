#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    size_t n;
    cin >> n;
    vector<double> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto const mn = *ranges::min_element(a);
    vector<int64_t> b(n);
    for (double i = 1; i <= 10000; i += 1) {
        ranges::transform(a, b.begin(), [&](auto const& x) { return lround(i / mn * x); });
        if (accumulate(b.begin(), b.end(), 0l, [&](auto const& x, auto const& y) { return gcd(x, y); }) != 1) {
            continue;
        }
        auto const d = sqrt(accumulate(b.begin(), b.end(), 0l, [&](auto const& x, auto const& y) { return x + y * y; }));
        if (ranges::all_of(views::iota(static_cast<size_t>(0), n), [&](auto const& id) {
                return abs(a[id] - static_cast<double>(b[id]) / d) < 1e-10;
            })) {
            for (auto const& x : b) {
                cout << x << '\n';
            }
            return 0;
        }
    }
}
