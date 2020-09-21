#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e5;

int N, K, a[mxN];

int cnt(int m) {
    int ret = 0;
    for (int i = 0, s = 0; i < N; ++i) {
        s += a[i];
        if (s >= m) ++ret, s = 0;
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> K;
    loop(i, N) cin >> a[i];

    int lo = 0, hi = accumulate(a, a + N, 0);
    while (lo ^ hi) {
        int m = (lo + hi + 1) >> 1;
        cnt(m) < K ? (hi = m - 1) : (lo = m);
    }
    cout << lo;
    return 0;
}