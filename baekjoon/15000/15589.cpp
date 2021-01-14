#include <bits/stdc++.h>
#define me segT[i]
#define lson segT[i << 1]
#define rson segT[i << 1 | 1]
using namespace std;

const int mxN = 1e5;

struct node {
    int cnt, len, t;
};

int sz, s[mxN], e[mxN], idx[mxN << 1];
node segT[mxN << 4];

inline void apply(int i, int val) {
    me.t = (me.cnt += val) ? me.len : i < sz ? lson.t + rson.t : 0;
}
void update(int l, int r, int val) {
    int l0 = l + sz, r0 = r + sz;
    for (l += sz, r += sz; l != r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, val);
        if (r & 1) apply(--r, val);
    }
    segT[l0].t = segT[l0].cnt ? segT[l0].len : 0;
    segT[r0].t = segT[r0].cnt ? segT[r0].len : 0;
    for (int i = l0; i; i >>= 1)
        me.t = me.cnt ? me.len : lson.t + rson.t;
    for (int i = r0; i; i >>= 1)
        me.t = me.cnt ? me.len : lson.t + rson.t;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> s[i] >> e[i];

    move(s, s + n, idx);
    move(e, e + n, idx + n);

    sort(idx, idx + (n << 1));
    sz = unique(idx, idx + (n << 1)) - idx - 1;

    for (int i = 0; i < n; ++i) {
        s[i] = lower_bound(idx, idx + sz, s[i]) - idx;
        e[i] = lower_bound(idx + s[i], idx + sz, e[i]) - idx;
    }

    for (int i = 0; i < sz; ++i)
        segT[i + sz].len = idx[i + 1] - idx[i];

    for (int i = sz - 1; i; --i)
        me.len = lson.len + rson.len;

    for (int i = 0; i < n; ++i)
        update(s[i], e[i], 1);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        update(s[i], e[i], -1);
        ans = max(ans, segT[1].t);
        update(s[i], e[i], 1);
    }
    cout << ans;
}