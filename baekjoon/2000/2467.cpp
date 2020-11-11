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
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);

    int x, y, mn = INT_MAX;
    for (int i = 0, j = N - 1, sum; i != j;) {
        sum = abs(a[i] + a[j]);
        if (sum < mn) mn = sum, x = a[i], y = a[j];
        a[i] + a[j] < 0 ? ++i : --j;
    }
    cout << x << ' ' << y;
}