#include <bits/stdc++.h>
#define a first
#define b second
#define A lazy[i].a
#define B lazy[i].b
#define left (i<<1)
#define right (i<<1|1)
#define len (r-l)
using namespace std;
using ll = long long;
using p = pair<int, ll>;

const int seg_N = 131072;

ll segT[seg_N << 1];
p lazy[seg_N << 1];

void init() {
    int N; cin >> N;
    for (int i = seg_N; i < seg_N + N; ++i)
        cin >> segT[i];
    for (int i = seg_N - 1; i; --i)
        segT[i] = segT[left] + segT[right];
}
ll sum(int l, int r, int i) {
    ll fst = A + B, lst = (ll)len * A + B;
    return segT[i] + (fst + lst) * len / 2;
}
void prop(int l, int r, int i) {
    segT[i] = sum(l, r, i);
    if (len ^ 1) {
        lazy[left].a += A, lazy[right].a += A;
        lazy[left].b += B, lazy[right].b += B + (ll)len / 2 * A;
    }
    A = 0, B = 0;
}
void update(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {++A, B += l - ql; return;}
    if (A) prop(l, r, i);

    int m = (l + r) >> 1;
    update(l, m, ql, qr, left), update(m, r, ql, qr, right);
    segT[i] = sum(l, m, left) + sum(m, r, right);
}
ll query(int l, int r, int qi, int i) {
    if (A) prop(l, r, i);
    if (len == 1) return segT[i];

    int m = (l + r) >> 1;
    return qi < m ? query(l, m, qi, left) : query(m, r, qi, right);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    init();

    int Q; cin >> Q;
    for (int l, r, i; Q--;) {
        char q; cin >> q;
        if (q == '1') {
            cin >> l >> r;
            update(0, seg_N, --l, r, 1);
        }
        else {
            cin >> i;
            cout << query(0, seg_N, --i, 1) << '\n';
        }
    }
    return 0;
}