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
    for (;;) {
        cin >> N;
        if (!N) break;

        int ans = 0;
        for (int k = 1; N - k * (k - 1) / 2 >= 2 * k; ++k)
            // a1 + a2 + ... + ak = N
            // a1 + (a1 + 1) + (a1 + 2) + ... + (a1 + k - 1) = N
            // ka1 + k(k - 1) / 2 = N
            // ka1 = N - k(k - 1) / 2
            // **(a1 > 1)**
            if ((N - k * (k - 1) / 2) % k == 0) ++ans;
        cout << ans << '\n';
    }
    return 0;
}