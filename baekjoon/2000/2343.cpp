#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN];

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

    int lo = *max_element(a, a + N), hi = 1e9;
    while (lo != hi) {
        int m = (lo + hi) >> 1;
        solve(m) ? (hi = m) : (lo = m + 1);
    }
    cout << lo;
    return 0;
}