#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    int m = 1;
    for (int x = N; x; x /= 10)
        if (x % 10)
            m = lcm(m, x % 10);

    int x = N % m;
    if (x == 0) {
        cout << N;
        return 0;
    }

    for (int d = 1;; ++d) {
        int mx = pow(10, d);
        int y = (x * mx) % m;
        for (int i = 0; i < mx; ++i)
            if ((y + i) % m == 0) {
                cout << N;
                cout << setfill('0') << setw(d) << i;
                return 0;
            }
    }
    return 0;
}