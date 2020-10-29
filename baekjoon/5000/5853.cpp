#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int mxN = 5e5;
const int sgN = 524288;

int lt[sgN << 1], ct[sgN << 1], rt[sgN << 1];
char lazy[sgN << 1];

inline int len(int i) {
    return sgN >> 31 - __builtin_clz(i);
}
inline int fst(int i) {
    int d = 31 - __builtin_clz(i);
    return (sgN >> d) * (i ^ 1 << d);
}
void prop(int i) {
    lazy[left] = lazy[right] = lazy[i];
    lt[left] = ct[left] = rt[left] = lt[right] = ct[right] = rt[right] = lazy[i] == 'I' ? 0 : len(left);
    lazy[i] = 0;
}
int query(int d, int l = 0, int r = sgN, int i = 1) {
    if (lt[i] >= d) return fst(i);
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    if (ct[left] >= d) return query(d, l, m, left);
    if (rt[left] + lt[right] >= d) return fst(right) - rt[left];
    return query(d, m, r, right);
}
void update(char q, int ql, int qr, int l = 0, int r = sgN, int i = 1) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        lazy[i] = q;
        lt[i] = ct[i] = rt[i] = q == 'I' ? 0 : len(i);
        return;
    }
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    update(q, ql, qr, l, m, left), update(q, ql, qr, m, r, right);
    lt[i] = lt[left] == len(left) ? lt[left] + lt[right] : lt[left];
    ct[i] = max({ct[left], ct[right], rt[left] + lt[right]});
    rt[i] = rt[right] == len(right) ? rt[right] + rt[left] : rt[right];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    fill(ct + sgN, ct + sgN + N, 1);
    move(ct + sgN, ct + sgN + N, lt + sgN);
    move(ct + sgN, ct + sgN + N, rt + sgN);

    for (int i = sgN - 1; i; --i) {
        lt[i] = lt[left] == len(left) ? lt[left] + lt[right] : lt[left];
        ct[i] = max({ct[left], ct[right], rt[left] + lt[right]});
        rt[i] = rt[right] == len(right) ? rt[right] + rt[left] : rt[right];
    }

    char q;
    int ans = 0;
    for (int x, d; M--;) {
        cin >> q;
        if (q == 'A') {
            cin >> d;
            if (ct[1] < d) ++ans;
            else {
                x = query(d);
                update('I', x, x + d);
            }
        } else {
            cin >> x >> d;
            --x;
            update('O', x, d);
        }
    }
    cout << ans;
}