#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr size_t MAX_N = 2e5;
    array<int, MAX_N> a;
    int t;
    cin >> t;
    for (int n, s; t--;) {
        cin >> n >> s;
        for (auto& x : a | ranges::views::take(n)) {
            cin >> x;
        }
        ranges::sort(a | ranges::views::take(n));
        auto parametric = [&]<typename T>(T lo, T hi) {
            auto f = [&](T mid) -> bool {
                auto prev_pos = ~0x3f3f3f3f;
                const auto maximum_seats = accumulate(a.begin(), a.begin() + n, 0, [&](const auto& acc, const auto& x) {
                    return x < prev_pos + mid ? acc : (prev_pos = x, acc + 1);
                });
                return maximum_seats >= s;
            };
            // // first true
            // while (lo != hi) {
            //     auto mid = lo + (hi - lo) / 2;
            //     f(mid) ? hi = mid : lo = mid + 1;
            // }
            // last true
            while (lo != hi) {
                auto mid = hi - (hi - lo) / 2;
                f(mid) ? lo = mid : hi = mid - 1;
            }
            return lo;
        };
        cout << parametric(1, a[n - 1] - a[0]) << '\n';
    }
}
