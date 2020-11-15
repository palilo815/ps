#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 2e5;

int a[mxN];

int min_xor(int l1, int r1, int l2, int r2, int msb) {
    if (l1 == r1 || l2 == r2) return 1 << 30;
    if (!msb) return 0;

    int m1 = find_if(a + l1, a + r1, [&](auto& x) { return x & msb; }) - a;
    int m2 = find_if(a + l2, a + r2, [&](auto& x) { return x & msb; }) - a;

    if (l1 == m1 && m2 == r2 || m1 == r1 && l2 == m2)
        return min_xor(l1, r1, l2, r2, msb >> 1) + msb;
    return min(min_xor(l1, m1, l2, m2, msb >> 1), min_xor(m1, r1, m2, r2, msb >> 1));
}
ll mst(int l, int r, int msb) {
    if (!msb || r - l <= 1) return 0;

    int m = find_if(a + l, a + r, [&](auto& x) { return x & msb; }) - a;

    ll ret = mst(l, m, msb >> 1) + mst(m, r, msb >> 1);
    if (l != m && m != r)
        ret += min_xor(l, m, m, r, msb >> 1) + msb;
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);

    cout << mst(0, N, 1 << 29);
}