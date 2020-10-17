#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;
using ll = long long;

struct line {
    int x, y1, y2, val;
};

const int mxN = 2e5;

line a[mxN << 1];
int M, idx[mxN << 1], cntT[mxN << 2], segT[mxN << 2], lenT[mxN << 2];

inline void apply(int i, int v) {
    segT[i] = (cntT[i] += v) ? lenT[i] : i < M ? segT[left] + segT[right] : 0;
}
void update(int l, int r, int v) {
    int l0 = l, r0 = r;
    for (; l != r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, v);
        if (r & 1) apply(--r, v);
    }
    segT[l0] = cntT[l0] ? lenT[l0] : 0;
    segT[r0] = cntT[r0] ? lenT[r0] : 0;
    for (int i = l0 >> 1; i; i >>= 1)
        segT[i] = cntT[i] ? lenT[i] : segT[left] + segT[right];
    for (int i = r0 >> 1; i; i >>= 1)
        segT[i] = cntT[i] ? lenT[i] : segT[left] + segT[right];
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
    for (int i = 0, x1, x2, y1, y2; i < N << 1; i += 2) {
        cin >> x1 >> x2 >> y1 >> y2;
        a[i] = {x1, y1, y2, 1};
        a[i | 1] = {x2, y1, y2, -1};
        idx[i] = y1, idx[i | 1] = y2;
    }

    sort(idx, idx + (N << 1));
    M = unique(idx, idx + (N << 1)) - idx;

    for (int i = 0; i < M - 1; ++i)
        lenT[i + M] = idx[i + 1] - idx[i];
    for (int i = M - 1; i; --i)
        lenT[i] = lenT[left] + lenT[right];

    sort(a, a + (N << 1), [&](auto& a, auto& b) {
        return a.x < b.x;
    });
    for (int i = 0; i < N << 1; ++i) {
        a[i].y1 = lower_bound(idx, idx + M, a[i].y1) - idx;
        a[i].y2 = lower_bound(idx + a[i].y1, idx + M, a[i].y2) - idx;
        a[i].y1 += M, a[i].y2 += M;
    }

    ll ans = 0;
    update(a[0].y1, a[0].y2, a[0].val);
    for (int i = 1; i < N << 1; ++i) {
        ans += (ll)segT[1] * (a[i].x - a[i - 1].x);
        update(a[i].y1, a[i].y2, a[i].val);
    }
    cout << ans;
}