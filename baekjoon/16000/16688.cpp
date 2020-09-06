#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int mxN = 1e3 + 1;

int a[mxN], dp[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    sort(a, a + N);
    dp[0] = 1;

    for (int i = 0, j; i < N; i = j) {
        for (j = i + 1; a[i] == a[j]; ++j)
            ;
        for (int k = K; k; --k)
            dp[k] = (dp[k] + (long long)dp[k - 1] * (j - i)) % mod;
    }
    cout << dp[K];
    return 0;
}