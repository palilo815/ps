#include <bits/stdc++.h>
using namespace std;

template <typename T>
class BIT {
    const int n;
    vector<T> tree;

public:
    BIT(int _n) : n(_n), tree(n + 1) {
        for (int i = 1; i <= n; ++i)
            tree[i] = i & -i;
    }

    void dec(int i) {
        assert(0 <= i and i < n);
        for (++i; i <= n; i += i & -i)
            --tree[i];
    }
    T query(int i) {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    T query(int l, int r) {
        assert(0 <= l and l <= r and r <= n);
        return query(r) - query(l);
    }
    T get(int i) {
        assert(0 <= i and i < n);
        return i & 1 ? query(i, i + 1) : tree[i + 1];
    }
    int lower_bound(T k) {
        if (k <= 0) return -1;
        int x = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
            if ((x | pw) <= n && tree[x | pw] < k)
                k -= tree[x |= pw];
        return x;
    }
    int upper_bound(T k) {
        if (k < 0) return -1;
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

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    auto compress = []<typename T>(vector<T>& a) -> int {
        vector<T> vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        for (auto& x : a)
            x = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
        return vals.size();
    };

    compress(a);

    vector<int> pos(n);
    for (int i = 0; i < n; ++i)
        pos[a[i]] = i;

    BIT<int> bit(n);
    int64_t ans = 0;
    for (const auto i : pos) {
        --n;
        int to_left = bit.query(i), to_right = n - to_left;
        ans += min(to_left, to_right);
        bit.dec(i);
    }
    cout << ans;
}