#include <bits/stdc++.h>
using namespace std;

const int mx = 100001;
const int oo = 0x3f3f3f3f;

int dp1[mx], dp2[mx];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    memset(dp1, 0x3f, sizeof(dp1));
    memset(dp2, 0x3f, sizeof(dp2));
    dp1[0] = dp2[0] = 0;

    int N;
    cin >> N;
    for (int x, s = 0; N--; s += x) {
        cin >> x;
        for (int i = s; ~i; --i)
            if (dp1[i] ^ oo)
                dp1[i + x] = min(dp1[i + x], dp1[i] + 1);
    }
    cin >> N;
    for (int x, s = 0; N--; s += x) {
        cin >> x;
        for (int i = s; ~i; --i)
            if (dp2[i] ^ oo)
                dp2[i + x] = min(dp2[i + x], dp2[i] + 1);
    }

    int ans = oo;
    for (int i = 1; i < mx; ++i)
        if (dp1[i] ^ oo && dp2[i] ^ oo)
            ans = min(ans, dp1[i] + dp2[i]);

    if (ans == oo)
        cout << "impossible";
    else
        cout << ans;
    return 0;
}