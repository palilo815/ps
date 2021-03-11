#include <bits/stdc++.h>
using namespace std;

struct full_seg {
    struct node_t {
        int64_t sum, lmax, mmax, rmax;
    };
    full_seg(int _n) : n(_n), height(__lg(_n - 1) + 1), size(1 << height),
                       tree(size << 1, e) {}

#define lson (i << 1)
#define rson (i << 1 | 1)
    void build(int k) {
        fill(tree.begin() + size, tree.end(), node_t {-k, -k, -k, -k});
        for (int i = size - 1; i; --i)
            pull(i);
    }
    void update(int idx, int64_t val) {
        assert(0 <= idx and idx < n);

        val += tree[idx += size].sum;
        tree[idx] = {val, val, val, val};
        while (idx >>= 1) pull(idx);
    }
    int64_t prod() {
        return tree[1].mmax;
    }

private:
    const node_t e = node_t {};
    const int n, height, size;
    vector<node_t> tree;

    void pull(int i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    node_t op(node_t lhs, node_t rhs) {
        auto sum = lhs.sum + rhs.sum;
        auto lmax = max(lhs.lmax, lhs.sum + rhs.lmax);
        auto mmax = max({lhs.mmax, rhs.mmax, lhs.rmax + rhs.lmax});
        auto rmax = max(rhs.rmax, rhs.sum + lhs.rmax);
        return {sum, lmax, mmax, rmax};
    }
#undef lson
#undef rson
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k, d;
    cin >> n >> m >> k >> d;

    const auto mx = int64_t(k) * d;

    full_seg seg(n);
    seg.build(k);
    for (int foot, x; m--;) {
        cin >> foot >> x, --foot;
        seg.update(foot, x);
        cout << (seg.prod() > mx ? "NIE\n" : "TAK\n");
    }
}