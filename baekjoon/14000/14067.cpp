#include <bits/stdc++.h>

constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;

template <typename T>
auto chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <typename T>
auto chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, l, r;
    cin >> n >> l >> r, ++r;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector dp(r - l, INF);
    for (const auto& x : a) {
        for (int i = r - l; i-- != 1;) {
            chmin(dp[i], dp[i - 1] + static_cast<int64_t>(abs(l + i - x)));
        }
        chmin(dp[0], static_cast<int64_t>(abs(l - x)));
    }
    cout << dp.back();
}
