#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN];

int bs(int l, int r, int lmb) {
    while (l != r) {
        int m = (l + r) >> 1;
        (a[m] & lmb) ? r = m : l = m + 1;
    }
    return l;
}
int solve(int l1, int r1, int l2, int r2, int lmb) {
    if (l1 == r1 || l2 == r2 || !lmb) return 0;

    int m1 = bs(l1, r1, lmb);
    int m2 = bs(l2, r2, lmb);

    if (l1 == m1 && l2 == m2 || m1 == r1 && m2 == r2)
        return solve(l1, r1, l2, r2, lmb >> 1);
    return max(solve(l1, m1, m2, r2, lmb >> 1), solve(m1, r1, l2, m2, lmb >> 1)) + lmb;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    sort(a, a + n);

    cout << solve(0, n, 0, n, 1 << 30);
}