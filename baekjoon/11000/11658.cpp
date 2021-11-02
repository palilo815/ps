#include <bits/stdc++.h>
using namespace std;

template <typename T>
class binary_indexed_tree {
    const size_t n;
    vector<vector<T>> tree;

public:
    binary_indexed_tree(size_t n) : n(n), tree(n + 1) {
        for (size_t i = 1; i <= n; ++i) {
            tree[i].resize(n + 1);
            for (size_t j = 1; j <= n; ++j) {
                cin >> tree[i][j];
            }
            for (size_t j = 1; j <= n; ++j) {
                if (j + (j & -j) <= n) {
                    tree[i][j + (j & -j)] += tree[i][j];
                }
            }
        }
        for (size_t j = 1; j <= n; ++j) {
            for (size_t i = 1; i <= n; ++i) {
                if (i + (i & -i) <= n) {
                    tree[i + (i & -i)][j] += tree[i][j];
                }
            }
        }
    }

    void update(size_t x, size_t y, T val) {
        for (auto i = x + 1; i <= n; i += i & -i) {
            for (auto j = y + 1; j <= n; j += j & -j) {
                tree[i][j] += val;
            }
        }
    }
    T prod(size_t x, size_t y) const {
        T ret {};
        for (auto i = x; i; i &= i - 1) {
            for (auto j = y; j; j &= j - 1) {
                ret += tree[i][j];
            }
        }
        return ret;
    }
    T prod(size_t x1, size_t y1, size_t x2, size_t y2) const {
        return prod(x1, y1) - prod(x1, y2) - prod(x2, y1) + prod(x2, y2);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    binary_indexed_tree<int> bit_2d(n);
    char op;
    for (int x1, x2, y1, y2; m--;) {
        cin >> op >> x1 >> y1, --x1, --y1;
        if (op == '0') {
            cin >> x2;
            bit_2d.update(x1, y1, x2 - bit_2d.prod(x1, y1, x1 + 1, y1 + 1));
        } else {
            cin >> x2 >> y2;
            cout << bit_2d.prod(x1, y1, x2, y2) << '\n';
        }
    }
}