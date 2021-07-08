#include <bits/stdc++.h>
using namespace std;

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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    vector<int> ord;
    for (int x; cin >> x; ord.emplace_back(x)) {
        ;
    }
    y_combinator([&](auto self, auto l, auto r) -> void {
        if (l == r) {
            return;
        }
        const auto root = *l;
        const auto pivot = upper_bound(l + 1, r, root);
        self(l + 1, pivot);
        self(pivot, r);
        cout << root << '\n';
    })(ord.begin(), ord.end());
}