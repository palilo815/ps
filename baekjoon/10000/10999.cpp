#include <bits/stdc++.h>
#define len (r-l)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;

const int seg_N = 1048576;

ll segT[seg_N << 1], lazy[seg_N << 1];

ll query(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return segT[i] + lazy[i] * len;
    if (lazy[i]) {
        if (l + 1 ^ r) lazy[left] += lazy[i], lazy[right] += lazy[i];
        segT[i] += lazy[i] * len;
        lazy[i] = 0;
    }

    int m = (l + r) >> 1;
    return query(l, m, ql, qr, left) + query(m, r, ql, qr, right);
}
void update(int l, int r, int ql, int qr, ll qv, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {lazy[i] += qv; return;}

    int m = (l + r) >> 1;
    update(l, m, ql, qr, qv, left), update(m, r, ql, qr, qv, right);
    segT[i] = segT[left] + segT[right] + lazy[left] * (len >> 1) + lazy[right] * (len >> 1);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q, Q2; cin >> N >> Q >> Q2;
    Q += Q2;
    for (int i = seg_N; i < seg_N + N; ++i)
        cin >> segT[i];

    for (int i = seg_N - 1; i; --i)
        segT[i] = segT[left] + segT[right];

    for (int i = 0, q, l, r; i < Q; ++i) {
        cin >> q >> l >> r; --l;
        if (q == 1) {
            ll v; cin >> v;
            update(0, seg_N, l, r, v, 1);
        }
        else cout << query(0, seg_N, l, r, 1) << '\n';
    }
    return 0;
}