#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

class segtree {
    struct node_t {
        int lsum, best, rsum;
        int is_full;
    };
    const node_t e = {};
    const int n, height, size;
    vector<node_t> tree;

public:
    segtree(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height),
                      tree(size << 1, e) {}

    node_t& operator[](int i) { return tree[size + i]; }
    void build() {
        for (int i = size - 1; i; --i)
            pull(i);
    }
    void update(int i, int j) {
        assert(0 <= i and i < n);
        assert(0 <= j and j < n);

        i += size, j += size;
        swap(tree[i], tree[j]);
        while ((i >>= 1) && (j >>= 1))
            pull(i), pull(j);
    }
    int get_best() { return tree[1].best; }

private:
    void pull(int i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    node_t op(node_t lhs, node_t rhs) {
        return node_t {
            .lsum = lhs.lsum + (lhs.is_full ? rhs.lsum : 0),
            .best = max({lhs.best, rhs.best, lhs.rsum + rhs.lsum}),
            .rsum = rhs.rsum + (rhs.is_full ? lhs.rsum : 0),
            .is_full = lhs.is_full && rhs.is_full};
    }
};

struct point {
    int x, y, val;
};

struct swap_pair {
    int dx, dy, i, j;
    swap_pair(int _dx, int _dy, int _i, int _j) : dx(_dx), dy(_dy), i(_i), j(_j) {}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<point> a(n);
    for (auto& [x, y, val] : a) {
        char c;
        cin >> x >> y >> c;
        val = (c == 'R');
    }

    sort(a.begin(), a.end(), [&](auto& lhs, auto& rhs) {
        return make_pair(lhs.x, lhs.y) < make_pair(rhs.x, rhs.y);
    });

    vector<swap_pair> swaps;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            swaps.emplace_back(a[j].x - a[i].x, a[j].y - a[i].y, i, j);

    sort(swaps.begin(), swaps.end(), [&](auto& lhs, auto& rhs) {
        return int64_t(lhs.dy) * rhs.dx > int64_t(rhs.dy) * lhs.dx;
    });

    segtree seg(n);
    for (int i = 0; i < n; ++i)
        seg[i] = {a[i].val, a[i].val, a[i].val, a[i].val};
    seg.build();

    vector<int> seg_id(n);
    iota(seg_id.begin(), seg_id.end(), 0);

    int ans = seg.get_best();
    for (int i = 0, j; i < int(swaps.size()); i = j) {
        for (j = i; j < int(swaps.size()); ++j) {
            if (int64_t(swaps[i].dy) * swaps[j].dx != int64_t(swaps[j].dy) * swaps[i].dx)
                break;
            seg.update(seg_id[swaps[j].i], seg_id[swaps[j].j]);
            swap(seg_id[swaps[j].i], seg_id[swaps[j].j]);
        }
        chmax(ans, seg.get_best());
    }
    cout << ans;
}