#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    a[N] = a[N - 1];

    int ans = 0;
    for (int i = 0, j; i < N; i = j) {
        for (j = i + 1; a[j - 1] ^ a[j]; ++j)
            ;
        ans = max(ans, j - i);
    }
    cout << ans;
    return 0;
}