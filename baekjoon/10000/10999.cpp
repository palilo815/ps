#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;
using ll = long long;

const int sgN = 1048576;

ll segT[sgN << 1], lazy[sgN << 1];

inline void prop(int i) {
    lazy[left] += lazy[i];
    lazy[right] += lazy[i];
    lazy[i] = 0;
}
inline void fix(int i, int len) {
    segT[i] = segT[left] + segT[right] + (lazy[left] + lazy[right]) * len;
}
ll query(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return segT[i] + lazy[i] * (r - l);
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    ll ret = query(l, m, ql, qr, left) + query(m, r, ql, qr, right);
    fix(i, (r - l) >> 1);
    return ret;
}
void update(int l, int r, int ql, int qr, ll qv, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        lazy[i] += qv;
        return;
    }

    int m = (l + r) >> 1;
    update(l, m, ql, qr, qv, left), update(m, r, ql, qr, qv, right);
    fix(i, (r - l) >> 1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, Q, Q2;
    cin >> N >> Q >> Q2;
    Q += Q2;
    for (int i = sgN; i < sgN + N; ++i)
        cin >> segT[i];

    for (int i = sgN - 1; i; --i)
        segT[i] = segT[left] + segT[right];

    for (int i = 0, q, l, r; i < Q; ++i) {
        cin >> q >> l >> r;
        --l;
        if (q == 1) {
            ll v;
            cin >> v;
            update(0, sgN, l, r, v, 1);
        } else
            cout << query(0, sgN, l, r, 1) << '\n';
    }
}