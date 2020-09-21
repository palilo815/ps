#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 2e5;

int a[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, d;
    cin >> N >> d;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);
    a[N] = INT_MAX;

    ll ans = 0;
    for (int i = 0, j; i < N; i = j) {
        for (j = i + 1; a[i] / d == a[j] / d; ++j)
            ;
        ans += (ll)(j - i) * (j - i - 1) / 2;
    }
    cout << ans;
    return 0;
}