#include <bits/extc++.h>

namespace std {
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}; // namespace std

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) cin >> x;
    for (auto& [x, y] : a) cin >> y;
    sort(a.begin(), a.end());
    int ans = 0;
    y_combinator([&](auto self, int sum_a, int hp, int res, int last) -> void {
        ans = max(ans, res);
        for (int i = last + 1; i < n; ++i) {
            const auto sum_a2 = sum_a + a[i].first;
            if (hp < sum_a2) continue;
            self(sum_a2, hp - sum_a2, res + a[i].second, i);
        }
    })(0, k, 0, -1);
    cout << ans;
}
