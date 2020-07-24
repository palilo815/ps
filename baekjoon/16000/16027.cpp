#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 2e5;

int sz, a[M], n[M];
int seg1[M << 1], seg2[M << 1];

void update(int segT[], int i, int v) {
    if (segT[i += sz] >= v) return;
    for (segT[i] = v; i > 1; i >>= 1)
        segT[i >> 1] = max(segT[i], segT[i ^ 1]);
}
int query(int segT[], int r) {
    int l = sz, ret = 0;
    for (r += sz; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max(ret, segT[l++]);
        if (r & 1) ret = max(ret, segT[--r]);
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, d; cin >> N >> d;
    loop(i, N) cin >> a[i];

    copy(a, a + N, n);
    sort(n, n + N);
    sz = unique(n, n + N) - n;

    loop(i, N) {
        int r1 = lower_bound(n, n + sz, a[i]) - n;
        int r2 = lower_bound(n, n + sz, a[i] + d) - n;

        update(seg2, r1, query(seg1, r2) + 1);
        update(seg1, r1, query(seg1, r1) + 1);
        update(seg2, r1, query(seg2, r1) + 1);
    }
    cout << seg2[1];
    return 0;
}