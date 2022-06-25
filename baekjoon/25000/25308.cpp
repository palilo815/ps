#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    array<int, 8> a, perm, stat;
    for (auto& x : a) cin >> x;
    iota(perm.begin(), perm.end(), 0);
    int ans {};
    do {
        transform(perm.begin(), perm.end(), stat.begin(), [&](const auto& x) {
            return a[x];
        });
        auto ok {true};
        for (int i {}; i < 8; ++i) {
            const auto a {stat[(i + 7) & 7]};
            const auto b {stat[(i + 1) & 7]};
            ok &= stat[i] > numbers::sqrt2 * (a * b) / (a + b) - 1e-9;
        }
        ans += ok;
    } while (next_permutation(perm.begin(), perm.end()));
    cout << ans;
}
