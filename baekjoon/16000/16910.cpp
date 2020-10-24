#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;
using ll = long long;

const int mxN = 1e5;
const int sgN = 262144;

int qq[mxN];
ll ql[mxN], qr[mxN];

ll idx[mxN << 1 | 1];

int segA[sgN << 1], segB[sgN << 1], lazy[sgN << 1];

inline int fst(int i) {
    int d = 31 - __builtin_clz(i);
    return (sgN >> d) * (i ^ 1 << d);
}
inline void prop(int i) {
    if (lazy[i] == 3)
        lazy[left] = 3 - lazy[left],
        lazy[right] = 3 - lazy[right];
    else
        lazy[left] = lazy[right] = lazy[i];
    lazy[i] = 0;
}
inline void fix(int i) {
    switch (lazy[left]) {
    case 1: segA[i] = fst(left), segB[i] = -1; break;
    case 2: segA[i] = -1, segB[i] = fst(left); break;
    case 3: segA[i] = segB[left], segB[i] = segA[left]; break;
    default: segA[i] = segA[left], segB[i] = segB[left];
    }

    if (segA[i] == -1) switch (lazy[right]) {
        case 0: segA[i] = segA[right]; break;
        case 1: segA[i] = fst(right); break;
        case 3: segA[i] = segB[right];
        }
    if (segB[i] == -1) switch (lazy[right]) {
        case 0: segB[i] = segB[right]; break;
        case 2: segB[i] = fst(right); break;
        case 3: segB[i] = segA[right];
        }
}
void update(int l, int r, int ql, int qr, int q, int i) {
    if (r <= ql || qr <= l) return;
    if (ql <= l && r <= qr) {
        lazy[i] = q == 3 ? 3 - lazy[i] : q;
        return;
    }
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    update(l, m, ql, qr, q, left), update(m, r, ql, qr, q, right);
    fix(i);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> qq[i] >> ql[i] >> qr[i];

    for (int i = 0; i < N; ++i)
        ++qr[i];

    move(ql, ql + N, idx);
    move(qr, qr + N, idx + N);
    idx[N << 1] = 1;

    sort(idx, idx + 2 * N + 1);
    int M = unique(idx, idx + 2 * N + 1) - idx;
    for (int i = 0; i < N; ++i)
        ql[i] = lower_bound(idx, idx + M, ql[i]) - idx,
        qr[i] = lower_bound(idx, idx + M, qr[i]) - idx;

    memset(segA, -1, sizeof(int) * 2 * sgN);
    iota(segB + sgN, segB + 2 * sgN, 0);
    for (int i = sgN - 1; i; --i)
        segB[i] = segB[left];

    for (int i = 0; i < N; ++i) {
        update(0, sgN, ql[i], qr[i], qq[i], 1);
        cout << idx[segB[1]] << '\n';
    }
}