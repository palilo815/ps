#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 1e5;

int N, Q, a[mxN];
ll total, fenwick[mxN + 1];

void update(int i, int x) {
    int diff = x - a[i];
    a[i] = x, total += diff;

    for (++i; i <= N; i += i & -i)
        fenwick[i] += diff;
}
ll read(int i) {
    ll ret = 0;
    for (++i; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> Q;
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        update(i, x);
    }

    for (int i, x, lo, hi; Q--;) {
        cin >> i >> x;
        update(i, x);

        for (lo = 0, hi = N; lo ^ hi;) {
            int m = (lo + hi) >> 1;
            ll L = read(m - 1);
            ll R = total - L - a[m];
            L < R ? (lo = m + 1) : (hi = m);
        }
        if (!lo) cout << "0\n";
        else {
            ll L = read(lo - 1);
            ll R = total - L - a[lo];
            ll c2 = (L - R) + ((a[lo] & 1) * (L == R ? 1 : -1));

            L -= a[lo - 1], R += a[lo];
            ll c1 = (R - L) + ((a[lo - 1] & 1) * (L == R ? 1 : -1));
            cout << (c1 > c2 ? lo : lo - 1) << '\n';
        }
    }
    return 0;
}