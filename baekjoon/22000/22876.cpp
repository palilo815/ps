#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

/**
 * @author  palilo 
 * @brief   segment tree (complete binary tree, i.e. every non-leaf nodes have 2 child nodes)
 * @warning must be used when (length of interval) or (order) of child nodes doesn't matter
 *          if it's matter, use "seg_full". it is full binary tree
 * @todo    e  <- identity element (op(e, any_value) = e)
 *          op <- unite two nodes
 */
template <typename node_t>
class segtree {
    // change this (1/2)
    const node_t e {};
    // change this (1/2)
    const size_t n;
    vector<node_t> tree;

public:
    segtree(size_t n) : n(n), tree(n << 1, e) {}

    node_t& operator[](size_t i) { return tree[n + i]; }
    void build() {
        for (size_t i = n; i--;) {
            pull(i);
        }
    }
    void set(size_t idx, node_t val) {
        assert(0 <= idx and idx < n);
        tree[idx += n] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t prod(size_t l, size_t r) const {
        assert(0 <= l and l <= r and r <= n);
        node_t ret = e;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ret = op(ret, tree[l++]);
            if (r & 1) ret = op(tree[--r], ret);
        }
        return ret;
    }
    node_t all_prod() const { return tree[1]; }
    void clear() {
        fill(tree.begin(), tree.end(), e);
    }

private:
    void pull(size_t i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    // change this (2/2)
    node_t op(node_t lhs, node_t rhs) const {
        return lhs.first > rhs.first ? node_t {lhs.first, max(lhs.second, rhs.first)}
                                     : node_t {rhs.first, max(rhs.second, lhs.first)};
    }
    // change this (2/2)
};

struct elem_t {
    int x, y, v;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int ans = -1;
    int n;
    cin >> n;
    vector<elem_t> a(n);
    for (auto& [x, y, v] : a) {
        cin >> x >> y >> v;
    }
    segtree<pair<int, int>> seg(size_t(1e6 + 1));
    auto solve = [&]() {
        // 3 vertical
        sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
            return lhs.x < rhs.x;
        });
        vector<int> sum;
        for (auto it = a.begin(), jt = a.begin(); it != a.end(); it = jt) {
            int cur = 0;
            for (; jt != a.end() && it->x == jt->x; ++jt) {
                cur += jt->v;
            }
            sum.emplace_back(cur);
        }
        const auto ed = min(sum.end(), sum.begin() + 3);
        nth_element(sum.begin(), ed, sum.end(), greater());
        chmax(ans, accumulate(sum.begin(), ed, 0));
        // 1 horizontal, 2 vertical
        for (const auto& [x, y, v] : a) {
            seg[y].first += v;
        }
        seg.build();
        for (auto it = a.begin(), jt = it; it != a.end();) {
            int hor = 0;
            for (; jt != a.end() && it->x == jt->x; ++jt) {
                hor += jt->v;
                auto val = seg[jt->y];
                val.first -= jt->v;
                seg.set(jt->y, val);
            }
            const auto ver = seg.all_prod();
            chmax(ans, hor + ver.first + ver.second);
            for (; it != jt; ++it) {
                auto val = seg[it->y];
                val.first += it->v;
                seg.set(it->y, val);
            }
        }
    };
    solve();
    seg.clear();
    for (auto& [x, y, v] : a) {
        swap(x, y);
    }
    solve();
    cout << ans;
}