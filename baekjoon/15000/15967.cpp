#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;
using ll = long long;

const int sgN = 1048576;

struct node {
    ll sum;
    int lazy;
};

node segT[sgN << 1];

inline ll calc(int i) {
    return segT[i].sum + (ll)segT[i].lazy * (sgN >> 31 - __builtin_clz(i));
}
inline void prop(int i) {
    segT[i].sum = calc(i);
    segT[left].lazy += segT[i].lazy, segT[right].lazy += segT[i].lazy;
    segT[i].lazy = 0;
}
void update(int ql, int qr, int qv, int l = 0, int r = sgN, int i = 1) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        segT[i].lazy += qv;
        return;
    }
    if (segT[i].lazy) prop(i);

    int m = (l + r) >> 1;
    update(ql, qr, qv, l, m, left), update(ql, qr, qv, m, r, right);
    segT[i].sum = calc(left) + calc(right);
}
ll query(int ql, int qr, int l = 0, int r = sgN, int i = 1) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return calc(i);

    if (segT[i].lazy) prop(i);
    int m = (l + r) >> 1;
    return query(ql, qr, l, m, left) + query(ql, qr, m, r, right);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, Q1, Q2;
    cin >> N >> Q1 >> Q2;
    Q1 += Q2;

    for (int i = sgN; i < sgN + N; ++i)
        cin >> segT[i].sum;

    for (int i = sgN - 1; i; --i)
        segT[i].sum = segT[left].sum + segT[right].sum;

    char q;
    for (int l, r, w; Q1--;) {
        cin >> q >> l >> r;
        --l;
        if (q == '1') cout << query(l, r) << '\n';
        else {
            cin >> w;
            update(l, r, w);
        }
    }
}