#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    auto next_bitset = [&](auto x) {
        const auto c {x & -x};
        const auto r {x + c};
        return (((x ^ r) >> 2) / c) | r;
    };
    int n, m, k;
    cin >> n >> m >> k;
    int total {}, ok {};
    for (auto x {(1 << m) - 1}; x < (1 << n); x = next_bitset(x)) {
        for (auto y {(1 << m) - 1}; y < (1 << n); y = next_bitset(y)) {
            ++total;
            ok += popcount(static_cast<unsigned>(x & y)) >= k;
        }
    }
    cout << fixed << setprecision(9)
         << static_cast<double>(ok) / total;
}
