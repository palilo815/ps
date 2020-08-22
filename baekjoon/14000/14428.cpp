#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;

const int mxN = 1e5;
const int sgN = 131072;

int a[mxN + 1], segT[sgN << 1];

void update(int i, int val) {
    a[i] = val;
    for (i = (i + sgN) >> 1; i; i >>= 1)
        segT[i] = a[segT[left]] > a[segT[right]] ? segT[right] : segT[left];
}
int query(int l, int r) {
    int ret = 0;
    for (l += sgN, r += sgN; l ^ r; l >>= 1, r >>= 1) {
        if (l & 1) {
            if (a[segT[l]] < a[ret] || a[segT[l]] == a[ret] && segT[l] < ret)
                ret = segT[l];
            ++l;
        }
        if (r & 1) {
            --r;
            if (a[segT[r]] < a[ret] || a[segT[r]] == a[ret] && segT[r] < ret)
                ret = segT[r];
        }
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> a[i];
    a[0] = INT_MAX;

    iota(segT + sgN, segT + sgN + N + 1, 0);
    for (int i = sgN - 1; i; --i)
        segT[i] = a[segT[left]] > a[segT[right]] ? segT[right] : segT[left];

    int Q; cin >> Q;
    for (int q, u, v; Q--;) {
        cin >> q >> u >> v;
        if (q == 1) update(u, v);
        else cout << query(u, v + 1) << '\n';
    }
    return 0;
}