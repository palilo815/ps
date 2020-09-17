#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int sgN = 1048576;

int segT[sgN << 1];
bool full[sgN << 1];

void update(int i, int v) {
    segT[i += sgN] += v;
    full[i] = segT[i] != 0;

    for (i >>= 1; i; i >>= 1) {
        segT[i] = full[left] ? (segT[left] + segT[right]) : segT[left];
        full[i] = full[left] & full[right];
    }
}
int query() {
    int i = 1;
    while (i < sgN && !full[left])
        i <<= 1;
    return segT[i];
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

    for (int q, k; Q--;) {
        cin >> q >> k;
        update(k - 1, q == 1 ? 1 : -1);
        cout << query() << '\n';
    }
    return 0;
}