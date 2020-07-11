#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;

const int seg_N = 262144;

ll minT[seg_N << 1], sumT[seg_N << 1], lazy[seg_N << 1];

void init(int N) {
    for (int i = 0; i < N; ++i)
        cin >> minT[seg_N + i];
    fill(minT + seg_N + N, minT + seg_N * 2, LLONG_MAX);
    copy(minT + seg_N, minT + seg_N + N, sumT + seg_N);

    for (int i = seg_N - 1; i; --i) {
        minT[i] = min(minT[left], minT[right]);
        sumT[i] = sumT[left] + sumT[right];
    }
}
void prop(int l, int r, int i) {
    minT[i] += lazy[i];
    sumT[i] += lazy[i] * (r - l);
    if (r - l ^ 1) lazy[left] += lazy[i], lazy[right] += lazy[i];
    lazy[i] = 0;
}
ll M(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return LLONG_MAX;
    if (ql <= l && r <= qr) return minT[i] + lazy[i];
    if (lazy[i]) prop(l, r, i);
    int m = (l + r) >> 1;
    return min(M(l, m, ql, qr, left), M(m, r, ql, qr, right));
}
ll S(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return sumT[i] + lazy[i] * (r - l);
    if (lazy[i]) prop(l, r, i);
    int m = (l + r) >> 1;
    return S(l, m, ql, qr, left) + S(m, r, ql, qr, right);
}
void P(int l, int r, int ql, int qr, int qv, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        lazy[i] += qv;
        return;
    }
    if (lazy[i]) prop(l, r, i);
    int m = (l + r) >> 1, cnt = (r - l) >> 1;
    P(l, m, ql, qr, qv, left), P(m, r, ql, qr, qv, right);
    minT[i] = min(minT[left] + lazy[left], minT[right] + lazy[right]);
    sumT[i] = sumT[left] + lazy[left] * cnt + sumT[right] + lazy[right] * cnt;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;

    init(N);

    for (int i = 0, l, r, v; i < Q; ++i) {
        char q; cin >> q >> l >> r;
        switch (q) {
        case 'M': cout << M(0, seg_N, --l, r, 1) << '\n'; break;
        case 'S': cout << S(0, seg_N, --l, r, 1) << '\n'; break;
        default:
            cin >> v;
            P(0, seg_N, --l, r, v, 1);
        }
    }
    return 0;
}