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
    auto operator()(Args&&... args) -> decltype(auto) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
auto y_combinator(Fun&& fun) -> decltype(auto) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}; // namespace std

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, b;
    cin >> n >> b;
    y_combinator([&](auto self, int x) -> void {
        if (!x) return;
        self(x / b);
        if (const auto d = x % b; d < 10) {
            cout << d;
        } else {
            cout << static_cast<char>(d - 10 + 'A');
        }
    })(n);
}
