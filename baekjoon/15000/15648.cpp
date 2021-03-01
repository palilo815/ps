#include <bits/stdc++.h>
using namespace std;

template <typename node_t>
struct complete_seg {
    complete_seg(int _n) : n(_n), tree(_n << 1, e) {}

#define lson (i << 1)
#define rson (i << 1 | 1)
    node_t& operator[](int i) { return tree[n + i]; }
    void build() {
        for (int i = n - 1; i; --i)
            pull(i);
    }
    void update(int idx, node_t val) {
        assert(0 <= idx and idx < n);

        tree[idx += n] = val;
        while (idx >>= 1) pull(idx);
    }
    node_t query(int l, int r) {
        if (l < 0) l = 0;
        if (n < r) r = n;

        node_t ret = e;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ret = op(ret, tree[l++]);
            if (r & 1) ret = op(tree[--r], ret);
        }
        return ret;
    }
    node_t product() {
        return tree[1];
    }

private:
    const node_t e = node_t {};
    const int n;
    vector<node_t> tree;

    void pull(int i) {
        tree[i] = op(tree[lson], tree[rson]);
    }
    node_t op(node_t lhs, node_t rhs) {
        return max(lhs, rhs);
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
    int n, k, d;
    cin >> n >> k >> d;

    vector<int> dp(k);
    complete_seg<int> seg(5e5);

    for (int x, res; n--;) {
        cin >> x, --x;
        res = max(dp[x % k], seg.query(x - d, x + d + 1)) + 1;
        dp[x % k] = res;
        seg.update(x, res);
    }
    cout << seg.product();
}