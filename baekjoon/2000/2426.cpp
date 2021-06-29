#include <bits/stdc++.h>
using namespace std;

template <typename T>
class BIT {
    const int n;
    vector<T> tree;

public:
    BIT(int _n) : n(_n), tree(n + 1) {}

    void update(int i, T val) {
        for (++i; i <= n; i += i & -i)
            tree[i] += val;
    }
    T query(int i) {
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    T query(int l, int r) {
        return query(r) - query(l);
    }
    T get(int i) {
        return i & 1 ? query(i, i + 1) : tree[i + 1];
    }
    int lower_bound(T k) {
        int x = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] < k)
                k -= tree[x |= pw];
        return x;
    }
    int upper_bound(T k) {
        int x = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
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

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    BIT<int> bit(n);
    for (int i = 0; i < n; ++i)
        bit.update(i, a[i] - (i ? a[i - 1] : 0));

    for (int x, y; m--;) {
        char op;
        cin >> op >> x >> y;

        if (op == 'F') {
            const int it = bit.lower_bound(y);
            if (it + x < n) {
                const int last_value = bit.query(it + x);
                const int lo = bit.lower_bound(last_value);
                const int hi = bit.upper_bound(last_value);

                bit.update(lo, -1);
                bit.update(hi - (x - (lo - it)), 1);
                bit.update(hi, -1);
            }
            bit.update(it, 1);
        } else {
            cout << bit.upper_bound(y) - bit.lower_bound(x) << '\n';
        }
    }
}