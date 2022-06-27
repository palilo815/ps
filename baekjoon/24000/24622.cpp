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
    int n;
    cin >> n;
    array<array<bool, 26>, 4> cubes {};
    for (auto& x : cubes) {
        for (auto i {6}; i--;) {
            char c;
            cin >> c;
            x[c - 'A'] = true;
        }
    }
    array<bool, 4> used {};
    for (string s; n--;) {
        used.fill(false);
        cin >> s;
        const auto yes {y_combinator([&](auto self, int i) -> bool {
            if (i == static_cast<int>(s.size())) return true;
            for (auto j {0}; j < 4; ++j) {
                if (!used[j] && cubes[j][s[i] - 'A']) {
                    used[j] = true;
                    if (self(i + 1)) return true;
                    used[j] = false;
                }
            }
            return false;
        })(0)};
        cout << (yes ? "YES" : "NO") << '\n';
    }
}
