#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e6;

int dp[mxN + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, a, b; cin >> N >> a >> b;

    memset(dp, 0x3f, sizeof(int) * N);
    for (int i = N; i; --i) {
        if (i >= a) dp[i - a] = min(dp[i - a], dp[i] + 1);
        if (i >= b) dp[i - b] = min(dp[i - b], dp[i] + 1);
    }

    for (int i = 0; i <= N; ++i)
        if (i >= dp[i]) {
            cout << i;
            break;
        }
    return 0;
}