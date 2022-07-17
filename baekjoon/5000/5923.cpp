#include <bits/stdc++.h>

template <typename T>
auto chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <typename T>
auto chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    array<int, 9> grid {};
    for (char s[10]; auto& x : grid) {
        cin >> s;
        for (int i = 0; i < 9; ++i) {
            x = x << 1 | (s[i] == '1');
        }
    }
    int dp[2][1 << 3][1 << 9];
    constexpr array BOX {0b000000111, 0b000111000, 0b111000000};
    constexpr auto SIZE = sizeof dp[0];
    auto cur = dp[0], prv = dp[1];
    memset(cur, 0x3f, SIZE);
    cur[0][0] = 0;
    for (int r = 0; r < 9; ++r) {
        swap(cur, prv);
        memset(cur, 0x3f, SIZE);
        for (int row_mask = 0; row_mask < (1 << 9); ++row_mask) {
            if (__builtin_parity(row_mask)) continue;
            const auto w = __builtin_popcount(grid[r] ^ row_mask);
            for (int col_state = 0; col_state < (1 << 9); ++col_state) {
                const auto j = col_state ^ row_mask;
                for (int box_state = 0; box_state < (1 << 3); ++box_state) {
                    const auto box_mask = __builtin_parity(row_mask & BOX[0]) |
                                          __builtin_parity(row_mask & BOX[1]) << 1 |
                                          __builtin_parity(row_mask & BOX[2]) << 2;
                    const auto i = box_state ^ box_mask;
                    chmin(cur[i][j], prv[box_state][col_state] + w);
                }
            }
        }
        if (r % 3 == 2) {
            memset(cur[1], 0x3f, SIZE / 8 * 7);
        }
    }
    cout << cur[0][0] << '\n';
}
