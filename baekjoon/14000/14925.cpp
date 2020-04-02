#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1; i<=n; ++i)
using namespace std;

const int MAX = 1000;

int DP[MAX + 1][MAX + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    LOOP(i, row) LOOP(j, col) {
        int x; cin >> x;
        DP[i][j] = (x ? 0 : 1);
    }

    int ans = 0;
    LOOP(i, row) LOOP(j, col) if (DP[i][j]) {
        DP[i][j] = min({ DP[i - 1][j - 1],DP[i - 1][j],DP[i][j - 1] }) + 1;
        ans = max(ans, DP[i][j]);
    }
    cout << ans;
    return 0;
}