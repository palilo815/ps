#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using ll = long long;

const int mxN = 123456;

char t[mxN];
int N, atk, a[mxN], h[mxN];

bool valid(ll m) {
    ll A = atk, H = m;
    loop(i, N) {
        if (t[i] == '1') {
            ll turn = (h[i] + A - 1) / A;
            H -= a[i] * (turn - 1);
            if (H <= 0) return false;
        } else
            A += a[i], H = min(m, H + h[i]);
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
    cin >> N >> atk;
    loop(i, N) cin >> t[i] >> a[i] >> h[i];

    ll lo = 1, hi = 123456000000000000LL;
    while (lo ^ hi) {
        ll m = (lo + hi) >> 1;
        valid(m) ? (hi = m) : (lo = m + 1);
    }
    cout << lo;
    return 0;
}