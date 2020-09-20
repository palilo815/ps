#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int N, K; cin >> N >> K;) {
        int ans = 1, tmp = K;
        for (int i = 2; i * i <= K; ++i)
            if (tmp % i == 0) {
                int c1 = 1, c2 = 0;
                for (tmp /= i; tmp % i == 0; tmp /= i, ++c1)
                    ;
                for (int j = i; j <= N; j *= i)
                    c2 += N / j;
                if (c1 > c2) c1 = c2;

                for (int j = 0; j < c1; ++j)
                    ans *= i;
            }
        if (tmp <= N) ans *= tmp;
        cout << ans << '\n';
    }
    return 0;
}