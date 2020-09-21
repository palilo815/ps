#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e4;

int a[mxN << 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    if (N == 1) {
        cout << "2\n1\n2";
        return 0;
    }

    a[0] = 2 * N - 3;
    for (int i = 1; i < N - 1; ++i)
        a[i] = 2 * N - 3 - i;
    a[N - 1] = 2 * N - 2;

    a[N] = 2 * N - 1;
    for (int i = N + 1; i < 2 * N - 1; ++i)
        a[i] = 2 * N - 1 - i;
    a[2 * N - 1] = 2 * N;

    long long ans = 0, total = (2 * N + 1) * N;
    for (int i = 0; i < N << 1; ++i) {
        ans += total * i;
        total -= a[i];
    }
    cout << ans << '\n';
    for (int i = 0; i < N; ++i)
        cout << a[i] << ' ';
    cout << '\n';
    for (int i = N; i < N << 1; ++i)
        cout << a[i] << ' ';
    return 0;
}