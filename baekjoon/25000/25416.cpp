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

template <typename T>
auto chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <typename T>
auto chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

constexpr std::array<std::pair<int, int>, 4> MOVE {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    array<array<int, 5>, 5> grid;
    for (auto& row : grid) {
        for (auto& x : row) {
            cin >> x;
        }
    }
    int x, y;
    cin >> x >> y;
    array<array<bool, 5>, 5> visited {};
    int ans = INT_MAX;
    y_combinator([&](auto self, int x, int y, int len) -> void {
        if (grid[x][y] == 1) {
            chmin(ans, len);
            return;
        }
        visited[x][y] = true;
        for (const auto& [dx, dy] : MOVE) {
            const auto xx = x + dx, yy = y + dy;
            if (xx == -1 || xx == 5 || yy == -1 || yy == 5 || grid[xx][yy] == -1 || visited[xx][yy]) continue;
            visited[xx][yy] = true;
            self(xx, yy, len + 1);
            visited[xx][yy] = false;
        }
    })(x, y, 0);
    cout << (ans != INT_MAX ? ans : -1);
}
