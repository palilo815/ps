#include <bits/stdc++.h>
using namespace std;

const int mxM = 4950;

int a[mxM];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    int M = N * (N - 1) / 2;
    for (int i = 0; i < M; ++i)
        cin >> a[i];

    sort(a, a + M);

    long long mx = 0;
    for (int i = 0, j = 1; i < M; i += j++)
        mx += a[i];

    cout << accumulate(a, a + N - 1, 0LL) << ' ' << mx;
}