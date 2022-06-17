#include <bits/stdc++.h>

template <typename T>
class SegmentTree {
    const size_t size;
    std::vector<T> tree;

public:
    SegmentTree() = default;
    SegmentTree(size_t n, const T& ID) : size(1 << (n ? std::__lg(n - 1) + 1 : 0)), tree(size << 1, ID) {}

    T& operator[](size_t i) { return tree[i | size]; }

    void build() {
        for (auto i {size}; --i;) {
            tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    void update(size_t i, T val) {
        tree[i |= size] = val;
        while (i >>= 1) tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
    }
    size_t query() const {
        size_t i {1};
        while (!(i & size)) {
            if (tree[i << 1] > tree[i << 1 | 1]) {
                i = i << 1 | 1;
            } else {
                i = i << 1;
            }
        }
        return i - size;
    }
};

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    SegmentTree seg(n, INT_MAX);
	for (auto i : views::iota(0, n)) {
        cin >> seg[i];
    }
    seg.build();
    int m;
    cin >> m;
    for (char op; m--;) {
        if (cin >> op; op == '1') {
            int i, v;
            cin >> i >> v, --i;
            seg.update(i, v);
        } else {
            cout << seg.query() + 1 << '\n';
        }
    }
}
