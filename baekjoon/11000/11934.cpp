#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
using namespace std;
using ll = long long;
using p = pair<int, int>;

const int mx = 2e5;

p a[mx], q[mx];
int M, maxT[mx << 1], sumT[mx << 1];

void update(int i) {
    for (i += M; i; i >>= 1)
        ++sumT[i];
}
int q_last(int l, int r) {
    int ret = -1;
    for (l += M, r += M; l ^ r; l >>= 1, r >>= 1) {
        if (l & 1) ret = max(ret, maxT[l++]);
        if (r & 1) ret = max(ret, maxT[--r]);
    }
    return ret;
}
int q_count(int l) {
    l += M;
    int ret = 0;
    for (int r = M << 1; l ^ r; l >>= 1, r >>= 1) {
        if (l & 1) ret += sumT[l++];
        if (r & 1) ret += sumT[--r];
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N >> M;
    loop(i, N) cin >> a[i].x >> a[i].y;
    loop(i, M) cin >> q[i].x;
    loop(i, M) q[i].y = i;

    sort(a, a + N, [&](p & a, p & b) {
        return max(a.x, a.y) > max(b.x, b.y);
    });
    sort(q, q + M);
    loop(i, M) maxT[M + i] = q[i].y;
    for (int i = M - 1; i; --i)
        maxT[i] = max(maxT[i << 1], maxT[i << 1 | 1]);

    ll ans = 0;
    int j = M - 1, lo, hi;
    loop(i, N) {
        a[i].x < a[i].y ? (lo = a[i].x, hi = a[i].y) : (hi = a[i].x, lo = a[i].y);
        for (; ~j && hi <= q[j].x; --j)
            update(q[j].y);

        int last = q_last(lower_bound(q, q + M, make_pair(lo, 0)) - q, upper_bound(q, q + M, make_pair(hi, 0)) - q);
        int cnt = q_count(last + 1);

        ans += ~last ? (cnt & 1 ? lo : hi) : (cnt & 1 ? a[i].y : a[i].x);
    }
    cout << ans;
    return 0;
}