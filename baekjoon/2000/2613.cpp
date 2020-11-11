#include <bits/stdc++.h>
using namespace std;

const int mxN = 300;

int a[mxN], ans[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
        cin >> a[i];

    auto solve = [&](int m) {
        for (int i = 0, cnt = 1, sum = 0; i < N; ++i) {
            if (sum + a[i] > m) {
                if (cnt++ == M) return false;
                sum = 0;
            }
            sum += a[i];
        }
        return true;
    };

    int lo = *max_element(a, a + N), hi = accumulate(a, a + N, 0);
    while (lo != hi) {
        int m = (lo + hi) >> 1;
        solve(m) ? hi = m : lo = m + 1;
    }

    for (int i = M, j = N; i; --i, --j)
        ans[i] = j;

    for (int i = 0, j = 0, k, sum; i < M; ++i, j = k) {
        for (k = j, sum = 0; k < ans[i + 1]; ++k) {
            if (sum + a[k] > lo) break;
            sum += a[k];
        }
        ans[i] = j;
        if (k == ans[i + 1]) break;
    }

    cout << lo << '\n';
    for (int i = 0; i < M; ++i)
        cout << ans[i + 1] - ans[i] << ' ';
}