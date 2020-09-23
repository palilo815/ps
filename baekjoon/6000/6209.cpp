#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4;

int N, M, a[mxN + 1];

bool solve(int m) {
    int pos = 0, rmv = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] - pos < m) {
            if (rmv++ == M) return false;
        } else
            pos = a[i];
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> a[0] >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> a[i];

    ++N;
    sort(a, a + N);

    int lo = 1, hi = a[N - 1];
    while (lo ^ hi) {
        int m = (lo + hi + 1) >> 1;
        solve(m) ? (lo = m) : (hi = m - 1);
    }
    cout << lo;
    return 0;
}