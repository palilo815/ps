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
    constexpr array next_colour = {'a', 'b', 'b', 'a'};
    int T, k;
    cin >> T >> k;
    vector grid(1 << k, string(1 << k, 0));
    for (int a, b; T--;) {
        cin >> a >> b, --a, --b;
        grid[a][b] = '@';
        y_combinator([&](auto self, int x, int y, int len, int hx, int hy, char colour) -> void {
            if (len == 2) {
                if (x != hx || y != hy) grid[x][y] = colour;
                if (x != hx || y + 1 != hy) grid[x][y + 1] = colour;
                if (x + 1 != hx || y != hy) grid[x + 1][y] = colour;
                if (x + 1 != hx || y + 1 != hy) grid[x + 1][y + 1] = colour;
                return;
            }
            len >>= 1;
            int hole_loc = -1, i = 0;
            for (const auto half_x : {x, x + len}) {
                for (const auto half_y : {y, y + len}) {
                    if (half_x <= hx && hx < half_x + len && half_y <= hy && hy < half_y + len) {
                        hole_loc = i;
                    }
                    ++i;
                }
            }
            i = 0;
            for (const auto cx : {x, x + len}) {
                for (const auto cy : {y, y + len}) {
                    if (hole_loc != i) {
                        grid[cx == x ? cx + len - 1 : cx][cy == y ? cy + len - 1 : cy] = 'c';
                        self(cx, cy, len, cx == x ? cx + len - 1 : cx, cy == y ? cy + len - 1 : cy, next_colour[i]);
                    } else {
                        self(cx, cy, len, hx, hy, next_colour[i]);
                    }
                    ++i;
                }
            }
        })(0, 0, 1 << k, a, b, 'c');
        for (const auto& row : grid) {
            cout << row << '\n';
        }
    }
}