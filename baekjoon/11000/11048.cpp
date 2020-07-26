#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int mxN = 1001;

int dp[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    LOOP(_, row) LOOP(i, col) {
        int x; cin >> x;
        dp[i] = max(dp[i - 1], dp[i]) + x;
    }
    cout << dp[col];
    return 0;
}