#include <bits/stdc++.h>
#define m ((l+r)>>1)
#define len (r-l)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;

const int seg_N = 131072;

ll minT[seg_N << 1], maxT[seg_N << 1], sumT[seg_N << 1];
ll lazy1[seg_N << 1];
int lazy2[seg_N << 1];

void build(int i) {
    minT[i] = min(minT[left], minT[right]);
    maxT[i] = max(maxT[left], maxT[right]);
    sumT[i] = sumT[left] + sumT[right];
}
int init() {
    int N, Q; cin >> N >> Q;
    for (int i = seg_N; i < seg_N + N; ++i)
        cin >> minT[i];

    memset(minT + seg_N + N, 0x3f, sizeof(ll) * (seg_N - N));
    copy(minT + seg_N, minT + seg_N + N, maxT + seg_N);
    copy(minT + seg_N, minT + seg_N + N, sumT + seg_N);

    for (int i = seg_N - 1; i; --i)
        build(i);
    return Q;
}
void prop(int i, int k) {
    if (lazy2[i]) {
        if (k ^ 1) {
            lazy1[left] = lazy1[right] = 0;
            lazy2[left] = lazy2[right] = lazy2[i];
        }
        minT[i] = maxT[i] = lazy2[i];
        sumT[i] = (ll)lazy2[i] * k;
        lazy2[i] = 0;
    }
    if (lazy1[i]) {
        if (k ^ 1) lazy1[left] += lazy1[i], lazy1[right] += lazy1[i];
        minT[i] += lazy1[i], maxT[i] += lazy1[i];
        sumT[i] += lazy1[i] * k;
        lazy1[i] = 0;
    }
}
void update1(int l, int r, int ql, int qr, int qv, int i) {
    prop(i, len);
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        lazy1[i] = qv;
        prop(i, len);
        return;
    }

    update1(l, m, ql, qr, qv, left), update1(m, r, ql, qr, qv, right);
    build(i);
}
void update2(int l, int r, int ql, int qr, int i) {
    prop(i, len);
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        int sq_min = sqrt(minT[i]), sq_max = sqrt(maxT[i]);
        if (sq_min == sq_max) {
            lazy2[i] = sq_min;
            prop(i, len);
            return;
        }
        if (minT[i] + 1 == maxT[i]) {
            lazy1[i] = sq_min - minT[i];
            prop(i, len);
            return;
        }
    }

    update2(l, m, ql, qr, left), update2(m, r, ql, qr, right);
    build(i);
}
ll query(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    prop(i, len);
    if (ql <= l && r <= qr) return sumT[i];

    return query(l, m, ql, qr, left) + query(m, r, ql, qr, right);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int Q = init();

    for (int i = 0, q, l, r, v; i < Q; ++i) {
        cin >> q >> l >> r; --l;
        switch (q) {
        case 1:
            cin >> v;
            update1(0, seg_N, l, r, v, 1); break;
        case 2: update2(0, seg_N, l, r, 1); break;
        default: cout << query(0, seg_N, l, r, 1) << '\n';
        }
    }
    return 0;
}