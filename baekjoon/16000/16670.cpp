#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;
using ll = long long;

const int sgN = 1048576;
const int mxQ = 3e5;

struct node {
    ll sum, mx;
};

node segT[sgN << 1];
int join[mxQ];

inline int fst(int i) {
    int d = 31 - __builtin_clz(i);
    return (sgN >> d) * (i ^ 1 << d);
}
void update(int i, int d) {
    i += sgN;
    segT[i].sum = d, segT[i].mx = fst(i) + d;

    while (i >>= 1)
        segT[i].sum = segT[left].sum + segT[right].sum,
        segT[i].mx = max(segT[left].mx + segT[right].sum, segT[right].mx);
}
ll query(int r) {
    ll ret = 0;
    vector<int> stk;

    r += sgN;
    for (int l = sgN; l != r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max(ret, segT[l++].mx);
        if (r & 1) stk.emplace_back(--r);
    }

    for (; !stk.empty(); stk.pop_back())
        ret = max({ret, ret + segT[stk.back()].sum, segT[stk.back()].mx});
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int Q;
    cin >> Q;

    for (int i = 0; i < sgN; ++i)
        segT[sgN + i].mx = i;

    for (int i = sgN - 1; i; --i)
        segT[i].mx = segT[right].mx;

    char q;
    for (int i = 0, t, d; i < Q; ++i) {
        cin >> q >> t;
        if (q == '?') cout << query(t + 1) - t << '\n';
        else {
            if (q == '+') {
                cin >> d;
                join[i] = t;
            } else {
                d = 0;
                t = join[t - 1];
            }
            update(t, d);
        }
    }
}