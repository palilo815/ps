#include <bits/stdc++.h>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
namespace std {
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
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;

    vector<bool> open(s.size());
    y_combinator([&](auto self, int l, int r) -> void {
        if (l == r) return;
        int m = min_element(s.begin() + l, s.begin() + r) - s.begin();
        open[m] = true;

        for (int i = 0; i < int(open.size()); ++i)
            if (open[i])
                cout << s[i];
        cout << '\n';

        self(m + 1, r);
        self(l, m);
    })(0, s.size());
}