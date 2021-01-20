#include <bits/stdc++.h>
#define lson (i << 1)
#define rson (i << 1 | 1)
using namespace std;

const int mxN = 25e4;
const int sgN = 262144;

int n, k, bit[mxN + 1], segT[sgN << 1];

void add(int i) {
    for (++i; i <= n; i += i & -i)
        ++bit[i];
}
void sub(int i) {
    for (++i; i <= n; i += i & -i)
        --bit[i];
}
int read(int l, int r) {
    int ret = 0;
    for (; l; l -= l & -l)
        ret -= bit[l];
    for (; r; r -= r & -r)
        ret += bit[r];
    return ret;
}
void update(int ql, int qr, int qx, int l = 0, int r = sgN, int i = 1) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr && (qx & segT[i]) == qx) return;
    if (l + 1 == r) {
        if (segT[i] == k) sub(l);
        if ((segT[i] |= qx) == k) add(l);
        return;
    }

    int m = (l + r) >> 1;
    update(ql, qr, qx, l, m, lson), update(ql, qr, qx, m, r, rson);
    segT[i] = segT[lson] & segT[rson];
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> segT[sgN + i];
    memset(segT + sgN + n, -1, sizeof(int) * (sgN - n));
    for (int i = sgN - 1; i; --i)
        segT[i] = segT[lson] & segT[rson];

    for (int i = 0; i < n; ++i)
        if (segT[sgN + i] == k)
            add(i);

    int m, l, r, x;
    cin >> m;
    for (char q; m--;) {
        cin >> q >> l >> r;
        --l;
        if (q == '2') cout << read(l, r) << '\n';
        else {
            cin >> x;
            update(l, r, x);
        }
    }
}