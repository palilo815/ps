#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    uint64_t board;
    for (int i = 0, x; i < n * n; ++i) {
        cin >> x;
        board = board << 1 | x;
    }
    array<uint64_t, 8> row_mask, col_mask;
    uint64_t mask = (1ULL << n) - 1;
    for (int i = 0; i < n; ++i) {
        row_mask[i] = mask << (i * n);
    }
    mask = 0;
    for (int i = 0; i < n; ++i) {
        mask |= 1ULL << (i * n);
    }
    for (int i = 0; i < n; ++i) {
        col_mask[i] = mask << i;
    }
    int ans = INT_MAX;
    for (int row_use = 0; row_use != 1 << n; ++row_use) {
        mask = board;
        for (int i = 0; i < n; ++i) {
            if (row_use >> i & 1) {
                mask ^= row_mask[i];
            }
        }
        for (int col_use = 0; col_use != 1 << n; ++col_use) {
            auto res = mask;
            for (int i = 0; i < n; ++i) {
                if (col_use >> i & 1) {
                    res ^= col_mask[i];
                }
            }
            const auto on = __builtin_popcountll(res);
            chmin(ans, min(on, n * n - on) + __builtin_popcount(row_use) + __builtin_popcount(col_use));
        }
    }
    cout << ans;
}