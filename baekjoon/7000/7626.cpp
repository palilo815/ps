#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct line {
    int x, y1, y2, w;
};

const int max_N = 2e5;
const int seg_N = 524288;

line a[max_N << 1];
int M, idx[seg_N];
int cntT[seg_N << 1], segT[seg_N << 1], lenT[seg_N << 1];

void apply(int i, int v) {
    cntT[i] += v;
    if (i >= seg_N) {
        segT[i] = cntT[i] ? lenT[i] : 0;
        i >>= 1;
    }
    for (; i; i >>= 1)
        segT[i] = cntT[i] ? lenT[i] : segT[i << 1] + segT[i << 1 | 1];
}
void update(int l, int r, int v) {
    l = lower_bound(idx, idx + M, l) - idx + seg_N;
    r = lower_bound(idx, idx + M, r) - idx + seg_N;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, v);
        if (r & 1) apply(--r, v);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0, x1, x2, y1, y2; i < N << 1; i += 2) {
        cin >> x1 >> x2 >> y1 >> y2;
        a[i] = {x1, y1, y2, 1};
        a[i + 1] = {x2, y1, y2, -1};
        idx[i] = y1, idx[i + 1] = y2;
    }
    sort(a, a + (N << 1), [&](line & a, line & b) -> bool {
        return a.x < b.x;
    });

    sort(idx, idx + (N << 1));
    M = unique(idx, idx + (N << 1)) - idx;
    for (int i = 0; i < M - 1; ++i)
        lenT[i + seg_N] = idx[i + 1] - idx[i];
    for (int i = seg_N - 1; i; --i)
        lenT[i] = lenT[i << 1] + lenT[i << 1 | 1];

    ll ans = 0;
    update(a[0].y1, a[0].y2, a[0].w);
    for (int i = 1; i < N << 1; ++i) {
        ans += (ll)segT[1] * (a[i].x - a[i - 1].x);
        update(a[i].y1, a[i].y2, a[i].w);
    }
    cout << ans;
    return 0;
}