#include <bits/stdc++.h>
using namespace std;

const int mxN = 25e4;

int fac[mxN + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = int64_t(fac[i - 1]) * i % m;

    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = (ans + int64_t(n - i + 1) * fac[i] % m * fac[n - i + 1] % m) % m;
    cout << ans;
}