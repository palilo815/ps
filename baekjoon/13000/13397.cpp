#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 5e3;

int N, M, a[mxN + 1];

int cnt(int m) {
    int ret = 0;
    for (int i = 0, j; i < N; i = j, ++ret) {
        int mn = a[i], mx = a[i];
        for (j = i + 1;; ++j) {
            if (a[j] > mx) mx = a[j];
            if (a[j] < mn) mn = a[j];
            if (mx - mn > m) break;
        }
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
    cin >> N >> M;
    loop(i, N) cin >> a[i];
    a[N] = INT_MAX;

    int lo = 0, hi = 1e4;
    while (lo ^ hi) {
        int m = (lo + hi) >> 1;
        cnt(m) > M ? (lo = m + 1) : (hi = m);
    }
    cout << lo;
    return 0;
}