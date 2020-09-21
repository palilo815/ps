#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e5;

int N, M, C, a[mxN];

bool valid(int m) {
    for (int i = 0, j, cnt = 0; i < N; i = j) {
        for (j = i + 1; j < i + C && a[j] - a[i] <= m; ++j)
            ;
        if (++cnt == M + 1) return false;
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
    cin >> N >> M >> C;
    loop(i, N) cin >> a[i];

    sort(a, a + N);

    int lo = 0, hi = 1e9;
    while (lo ^ hi) {
        int m = (lo + hi) >> 1;
        valid(m) ? (hi = m) : (lo = m + 1);
    }
    cout << lo;
    return 0;
}