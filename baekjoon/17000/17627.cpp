#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> vt;
    int n;

    BIT(int n) : n(n), vt(n + 1) {}
    void update(int i, int val) {
        for (++i; i <= n; i += i & -i)
            vt[i] ^= val;
    }
    int query(int i) const {
        int ret = 0;
        for (; i; i -= i & -i)
            ret ^= vt[i];
        return ret;
    }
    int query(int l, int r) const {
        return query(r) ^ query(l);
    }
    int access(int i) const {
        return i & 1 ? query(i, i + 1) : vt[i + 1];
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    BIT even((n >> 1) + (n & 1)), odd(n >> 1);
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        (i & 1 ? odd : even).update(i >> 1, x);
    }

    char op;
    for (int l, r; m--;) {
        cin >> op >> l >> r, --l;
        BIT& bit = l & 1 ? odd : even;

        if (op == '1') {
            l >>= 1;
            bit.update(l, bit.access(l) ^ r);
        } else
            cout << (r - l & 1 ? bit.query(l >> 1, (r + 1) >> 1) : 0) << '\n';
    }
}