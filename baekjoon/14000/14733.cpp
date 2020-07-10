#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct line {
    int x, y1, y2, w;
};

const int max_N = 3000;
const int seg_N = 131072;
const int Y = seg_N + 50000;

line a[max_N << 1];
int cntT[seg_N << 1], segT[seg_N << 1];

void apply(int i, int v, int k) {
    cntT[i] += v;
    if (k == 1) {
        segT[i] = cntT[i] != 0;
        i >>= 1, k <<= 1;
    }
    for (; i; i >>= 1, k <<= 1)
        segT[i] = cntT[i] ? k : segT[i << 1] + segT[i << 1 | 1];
}
void update(int l, int r, int v) {
    l += Y, r += Y;
    for (int k = 1; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, v, k);
        if (r & 1) apply(--r, v, k);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0, x1, y1, x2, y2; i < N << 1; i += 2) {
        cin >> x1 >> y1 >> x2 >> y2;
        a[i] = {x1, y1, y2, 1};
        a[i + 1] = {x2, y1, y2, -1};
    }
    sort(a, a + (N << 1), [&](line & a, line & b) -> bool {
        return a.x < b.x;
    });

    ll ans = 0;
    update(a[0].y1, a[0].y2, a[0].w);
    for (int i = 1; i < N << 1; ++i) {
        ans += (ll)segT[1] * (a[i].x - a[i - 1].x);
        update(a[i].y1, a[i].y2, a[i].w);
    }
    cout << ans;
    return 0;
}