#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int MAX = 1000;

char board[MAX + 1][MAX + 1];
int DP[MAX + 2][MAX + 2];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(DP, -1, sizeof(DP));
    int row, col; cin >> row >> col;
    LOOP(i, row) LOOP(j, col) {
        cin >> board[i][j];
        if (board[i][j] == 'R') DP[i][j] = 0;
    }

    int ans = -1;
    LOOP(c, col) LOOP(r, row) if (DP[r][c] != -1) {
        if (board[r][c] == '#') continue;
        if (board[r][c] == 'C') ++DP[r][c];
        else if (board[r][c] == 'O') ans = max(ans, DP[r][c]);
        DP[r - 1][c + 1] = max(DP[r - 1][c + 1], DP[r][c]);
        DP[r][c + 1] = max(DP[r][c + 1], DP[r][c]);
        DP[r + 1][c + 1] = max(DP[r + 1][c + 1], DP[r][c]);
    }
    cout << ans;
    return 0;
}