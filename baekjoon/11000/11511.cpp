#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 10007;

template <typename node_t>
struct segtree {
    segtree(int _n, int _c) : n(_n), c(_c),
                              tree(_n << 1, e) {}

    node_t& operator[](int i) { return tree[n + i]; }
    void build() {
        for (int i = n - 1; i; --i)
            pull(i);
    }
    void set(int idx, int va, int vb) {
        assert(0 <= idx and idx < n);

        idx += n;
        tree[idx][0] = vb, tree[idx][1] = va;
        while (idx >>= 1) pull(idx);
    }
    int all_prod() {
        return accumulate(tree[1].begin(), tree[1].begin() + c, 0) % mod;
    }

private:
#define lson (i << 1)
#define rson (i << 1 | 1)
    const node_t e = node_t {};
    const int n, c;
    vector<node_t> tree;

    void pull(int i) {
        for (int t = 0; t < c; ++t) {
            int sum = 0;
            for (int j = 0; j <= t; ++j) {
                sum += tree[lson][j] * tree[rson][t - j];
                sum %= mod;
            }
            tree[i][t] = sum;
        }
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
    int n, c;
    cin >> n >> c;

    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    int total = 1;
    for (int i = 0; i < n; ++i) {
        a[i] %= mod, b[i] %= mod;
        total *= a[i] + b[i];
        total %= mod;
    }

    int q;
    cin >> q;

    segtree<array<int, 20>> seg(n, c);
    for (int i = 0; i < n; ++i)
        seg[i][0] = b[i], seg[i][1] = a[i];
    seg.build();

    auto inv = [&](int x) {
        int r = 1;
        for (int p = mod - 2; p; p >>= 1) {
            if (p & 1) r = r * x % mod;
            x = x * x % mod;
        }
        return r;
    };

    for (int i, va, vb, ans; q--;) {
        cin >> i >> va >> vb, --i;

        total = total * inv((a[i] + b[i]) % mod) % mod;
        a[i] = va % mod, b[i] = vb % mod;
        total = total * (a[i] + b[i]) % mod;

        seg.set(i, a[i], b[i]);
        ans = total - seg.all_prod();
        cout << ans + (ans < 0 ? mod : 0) << '\n';
    }
}