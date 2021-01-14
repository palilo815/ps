#include <bits/stdc++.h>
using namespace std;

const int mxQ = 1e2;
const int mod = 1e9 + 7;

struct BIT {
    int n;
    vector<int> vt;

    BIT(int n) : n(n + 1), vt(n + 1) {}
    void reset() {
        fill(vt.begin(), vt.end(), 0);
    }
    void add(int i) {
        for (++i; i < n; i += i & -i)
            ++vt[i];
    }
    int sum(int i) {
        int ret = 0;
        for (++i; i; i -= i & -i)
            ret += vt[i];
        return ret;
    }
};

int query[mxQ], lo[mxQ], hi[mxQ], ord[mxQ];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, x0, a, b, q;
    cin >> n >> x0 >> a >> b >> q;

    for (int i = 0; i < q; ++i)
        cin >> query[i];

    fill(hi, hi + q, mod);

    BIT bit(q);

    for (int _ = 0; _ < 30; ++_) {
        bit.reset();

        for (int i = 0; i < q; ++i)
            ord[i] = (lo[i] + hi[i]) >> 1;
        sort(ord, ord + q);
        int sz = unique(ord, ord + q) - ord;

        for (int i = 0, x = x0; i < n; ++i, x = (int64_t(x) * a + b) % mod)
            bit.add(lower_bound(ord, ord + sz, x) - ord);

        for (int i = 0; i < q; ++i) {
            int mid = (lo[i] + hi[i]) >> 1,
                idx = lower_bound(ord, ord + sz, mid) - ord;
            query[i] < bit.sum(idx) ? hi[i] = mid : lo[i] = mid + 1;
        }
    }

    cout << accumulate(lo, lo + q, 0ll);
}