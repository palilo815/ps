#include <bits/stdc++.h>
using namespace std;
const int seg_N = 262144 - 1;

int segT[seg_N];
int lazy[seg_N];

void update(int ql, int qr, int qv, int l, int r, int i) {
    if (lazy[i]) {
        segT[i] = lazy[i];
        if (l != r)
            lazy[2 * i + 1] = lazy[i],
            lazy[2 * i + 2] = lazy[i];
        lazy[i] = 0;
    }

    if (ql <= l && r <= qr) {
        segT[i] = qv;
        if (l != r)
            lazy[2 * i + 1] = qv,
            lazy[2 * i + 2] = qv;
        return;
    }
    if (qr < l || r < ql) return;

    int m = (l + r) >> 1;
    update(ql, qr, qv, l, m, 2 * i + 1);
    update(ql, qr, qv, m + 1, r, 2 * i + 2);
    segT[i] = segT[2 * i + 1] | segT[2 * i + 2];
}
int query(int ql, int qr, int l, int r, int i) {
    if (lazy[i]) {
        segT[i] = lazy[i];
        if (l != r)
            lazy[2 * i + 1] = lazy[i],
            lazy[2 * i + 2] = lazy[i];
        lazy[i] = 0;
    }

    if (ql <= l && r <= qr) return segT[i];
    if (qr < l || r < ql) return 0;

    int m = (l + r) >> 1;
    return query(ql, qr, l, m, 2 * i + 1) | query(ql, qr, m + 1, r, 2 * i + 2);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    fill(segT, segT + seg_N, 2);
    int N, T, Q; cin >> N >> T >> Q;
    while (Q--) {
        char q; cin >> q;
        int ql, qr; cin >> ql >> qr;
        if (ql > qr) swap(ql, qr);
        if (q == 'C') {
            int c; cin >> c;
            update(ql, qr, 1 << c, 1, N, 0);
        }
        else cout << __builtin_popcount(query(ql, qr, 1, N, 0)) << '\n';
    }
    return 0;
}