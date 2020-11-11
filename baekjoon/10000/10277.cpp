#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int mxO = 5e4;
const int sgN = 131072;
const int INF = 0x3f3f3f3f;

struct query {
    int l, r, x;
};
struct node {
    int mn, mx, lazy;
};

query q[mxO];
int ord[mxO << 1];
node segT[sgN << 1];

inline void prop(int i) {
    segT[i].mn += segT[i].lazy;
    segT[i].mx += segT[i].lazy;
    segT[left].lazy += segT[i].lazy;
    segT[right].lazy += segT[i].lazy;
    segT[i].lazy = 0;
}
int min_query(int ql, int qr, int l = 0, int r = sgN, int i = 1) {
    if (qr <= l || r <= ql) return INF;
    if (ql <= l && r <= qr) return segT[i].mn + segT[i].lazy;
    if (segT[i].lazy) prop(i);

    int m = (l + r) >> 1;
    return min(min_query(ql, qr, l, m, left), min_query(ql, qr, m, r, right));
}
int max_query(int ql, int qr, int l = 0, int r = sgN, int i = 1) {
    if (qr <= l || r <= ql) return -INF;
    if (ql <= l && r <= qr) return segT[i].mx + segT[i].lazy;
    if (segT[i].lazy) prop(i);

    int m = (l + r) >> 1;
    return max(max_query(ql, qr, l, m, left), max_query(ql, qr, m, r, right));
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
    segT[i].mn = min(segT[left].mn + segT[left].lazy, segT[right].mn + segT[right].lazy);
    segT[i].mx = max(segT[left].mx + segT[left].lazy, segT[right].mx + segT[right].lazy);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int C, N, O;
    cin >> C >> N >> O;

    char op[12];
    for (int i = 0; i < O; ++i) {
        cin >> op;
        if (op[0] == 's') {
            cin >> q[i].l;
            q[i].r = q[i].x = INF;
        } else if (op[0] == 'c') {
            cin >> q[i].l >> q[i].x;
            q[i].r = INF;
        } else {
            cin >> q[i].l >> q[i].r >> q[i].x;
            ++q[i].r;
        }
    }

    int M = 0;
    for (int i = 0; i < O; ++i) {
        if (q[i].l != INF) ord[M++] = q[i].l;
        if (q[i].r != INF) ord[M++] = q[i].r;
    }

    sort(ord, ord + M);
    M = unique(ord, ord + M) - ord;

    for (int i = 0; i < O; ++i) {
        if (q[i].l != INF) q[i].l = lower_bound(ord, ord + M, q[i].l) - ord;
        if (q[i].r != INF) q[i].r = lower_bound(ord + q[i].l, ord + M, q[i].r) - ord;
    }

    for (int i = 0, qr, qv; i < O; ++i) {
        if (q[i].x == INF) cout << min_query(q[i].l, q[i].l + 1) << '\n';
        else {
            qr = q[i].r == INF ? q[i].l + 1 : q[i].r;
            if (q[i].x > 0)
                qv = min(q[i].x, N - max_query(q[i].l, qr));
            else
                qv = max(q[i].x, -min_query(q[i].l, qr));
            update(q[i].l, qr, qv);
            cout << qv << '\n';
        }
    }
}