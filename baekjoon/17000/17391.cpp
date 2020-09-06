#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 300;

int mat[mxN][mxN], dp[mxN][mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    loop(r, row) loop(c, col) {
        for (int i = c + 1, j = min(col, c + mat[r][c] + 1); i < j; ++i)
            dp[r][i] = min(dp[r][i], dp[r][c] + 1);
        for (int i = r + 1, j = min(row, r + mat[r][c] + 1); i < j; ++i)
            dp[i][c] = min(dp[i][c], dp[r][c] + 1);
    }
    cout << dp[row - 1][col - 1];
    return 0;
}