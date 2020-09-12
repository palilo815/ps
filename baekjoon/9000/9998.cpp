#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

const int mxN = 3e5;

int N;
ll a[mxN], b[mxN];

ll solve(ll m) {
    ll ret = 0;
    loop(i, N) ret += abs(m + abs(N / 2 - i) - a[i]);
    loop(i, N) ret += abs(m + abs(N / 2 - i) - b[i]);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> a[i];
    loop(i, N) cin >> b[i];

    ll lo = 0, hi = 1e12 - (N >> 1);
    while (lo ^ hi) {
        ll m = (lo + hi) >> 1;
        solve(m) < solve(m + 1) ? (hi = m) : (lo = m + 1);
    }
    cout << solve(lo);
    return 0;
}