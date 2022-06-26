#include <bits/stdc++.h>

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
    vector<int> breed(n);
    vector<tuple<int, int, int>> relations(k);
    for (auto& [x, y, z] : relations) {
        char c;
        cin >> c >> y >> z, --y, --z;
        x = c == 'S';
    }
    int ans {};
    y_combinator([&](auto self, int i) -> void {
        if (i == n) {
            ans += none_of(relations.begin(), relations.end(), [&](auto& r) {
                return get<0>(r) ^ (breed[get<1>(r)] == breed[get<2>(r)]);
            });
            return;
        }
        for (int b {}; b < 3; ++b) {
            breed[i] = b;
            self(i + 1);
        }
    })(1);
    cout << ans * 3;
}
