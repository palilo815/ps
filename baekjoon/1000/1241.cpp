#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e5;

int a[mxN], cnt[mxN * 10 + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    loop(i, N) cin >> a[i];
    loop(i, N) cnt[a[i]]++;

    loop(i, N) {
        if (a[i] == 1) cout << cnt[1] - 1 << '\n';
        else {
            int ans = cnt[1] + cnt[a[i]] - 1, j = 2;
            for (; j * j < a[i]; ++j)
                if (a[i] % j == 0)
                    ans += cnt[j] + cnt[a[i] / j];
            if (j * j == a[i]) ans += cnt[j];
            cout << ans << '\n';
        }
    }
    return 0;
}