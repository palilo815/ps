#include <bits/stdc++.h>
#define m ((l+r)>>1)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
struct block {
    int l, r;
};

const int max_N = 1e5;
const int seg_N = 262144;

block b[max_N];
int N, M, idx[max_N << 1];
int segT[seg_N << 1], lazy[seg_N << 1];

void init() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> b[i].r >> b[i].l;
        b[i].r += b[i].l;
    }
    memcpy(idx, b, sizeof(int) * (N << 1));
    sort(idx, idx + (N << 1));
    M = unique(idx, idx + (N << 1)) - idx;
}
void prop(int i) {
    segT[i] = lazy[i];
    if (i < seg_N) lazy[left] = lazy[i], lazy[right] = lazy[i];
    lazy[i] = 0;
}
void U(int l, int r, int ql, int qr, int qv, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {lazy[i] = qv; return;}
    if (lazy[i]) prop(i);
    U(l, m, ql, qr, qv, left), U(m, r, ql, qr, qv, right);
    segT[i] = max({segT[left], lazy[left], segT[right], lazy[right]});
}
int Q(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return max(segT[i], lazy[i]);
    if (lazy[i]) prop(i);
    return max(Q(l, m, ql, qr, left), Q(m, r, ql, qr, right));
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    init();
    for (int i = 0, l, r; i < N; ++i) {
        l = lower_bound(idx, idx + M, b[i].l) - idx;
        r = lower_bound(idx, idx + M, b[i].r) - idx;
        U(0, seg_N, l, r, Q(0, seg_N, l, r, 1) + 1, 1);
    }
    cout << Q(0, seg_N, 0, M, 1);
    return 0;
}