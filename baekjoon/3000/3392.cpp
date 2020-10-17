#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

struct line {
    int x, y1, y2, val;
};

const int mxN = 1e4;
const int sgN = 32768;

line a[mxN << 1];
int cntT[sgN << 1], segT[sgN << 1];

inline void apply(int i, int v, int k) {
    segT[i] = (cntT[i] += v) ? k : k == 1 ? 0 : segT[left] + segT[right];
}
void update(int l, int r, int v) {
    int l0 = l += sgN, r0 = r += sgN;
    for (int k = 1; l != r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, v, k);
        if (r & 1) apply(--r, v, k);
    }
    segT[l0] = cntT[l0] != 0;
    segT[r0] = cntT[r0] != 0;
    for (int i = l0 >> 1, k = 2; i; i >>= 1, k <<= 1)
        segT[i] = cntT[i] ? k : segT[left] + segT[right];
    for (int i = r0 >> 1, k = 2; i; i >>= 1, k <<= 1)
        segT[i] = cntT[i] ? k : segT[left] + segT[right];
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
    for (int i = 0, x1, y1, x2, y2; i < N << 1; i += 2) {
        cin >> x1 >> y1 >> x2 >> y2;
        a[i] = {x1, y1, y2, 1};
        a[i | 1] = {x2, y1, y2, -1};
    }

    sort(a, a + (N << 1), [&](auto& a, auto& b) {
        return a.x < b.x;
    });

    int ans = 0;
    update(a[0].y1, a[0].y2, a[0].val);
    for (int i = 1; i < N << 1; ++i) {
        ans += segT[1] * (a[i].x - a[i - 1].x);
        update(a[i].y1, a[i].y2, a[i].val);
    }
    cout << ans;
}