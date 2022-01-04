#include <bits/stdc++.h>
using namespace std;

template <typename T>
class binary_indexed_tree {
    const size_t n;
    vector<T> tree;

public:
    binary_indexed_tree(size_t n) : n(n), tree(n + 1) {}

    void update(size_t i) {
        assert(0 <= i and i <= n);
        for (++i; i <= n; i += i & -i)
            ++tree[i];
    }
    // return the sum of the range [0, i)
    T query(size_t i) const {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    // return the sum of the range [l, r)
    T query(size_t l, size_t r) const {
        return query(r) - query(l);
    }
    // return a[i]
    T get(size_t i) const {
        assert(0 <= i and i < n);
        return i & 1 ? query(i, i + 1) : tree[i + 1];
    }
    // return minimum i s.t. sum[0...i] >= k
    size_t lower_bound(T k) const {
        size_t x = 0;
        for (size_t pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] < k)
                k -= tree[x |= pw];
        return x;
    }
    // return minimum i s.t. sum[0...i] > k
    size_t upper_bound(T k) const {
        size_t x = 0;
        for (size_t pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] <= k)
                k -= tree[x |= pw];
        return x;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto vals = a;
    ranges::sort(vals, greater());
    for (auto& x : a) {
        x = ranges::lower_bound(vals, x, greater()) - vals.begin();
    }
    binary_indexed_tree<int> bit(n);
    for (int i = 0; i < n; ++i) {
        bit.update(a[i]);
        if (const int64_t cnt_larger = bit.query(a[i]);
            !cnt_larger) {
            // nothing happens
        } else if (k > cnt_larger + 1) {
            k -= cnt_larger + 1;
        } else {
            return cout << vals[bit.lower_bound(k)], 0;
        }
    }
    cout << -1;
}
