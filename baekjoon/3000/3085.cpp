#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int N;
char board[50][50];

int cnt(int r, int c, int dr, int dc) {
    int ret = 0, sum = 0;
    for (char x = board[r][c]; r < N && c < N; r += dr, c += dc) {
        if (board[r][c] == x) ++sum;
        else {
            ret = max(ret, sum);
            sum = 1;
            x = board[r][c];
        }
    }
    return max(ret, sum);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) loop(j, N) cin >> board[i][j];

    int ans = 0;
    loop(i, N) ans = max(ans, cnt(i, 0, 0, 1));
    loop(j, N) ans = max(ans, cnt(0, j, 1, 0));
    loop(i, N) loop(j, N) {
        if (j + 1 < N) {
            swap(board[i][j], board[i][j + 1]);
            ans = max(ans, cnt(i, 0, 0, 1));
            ans = max(ans, cnt(0, j, 1, 0));
            ans = max(ans, cnt(0, j + 1, 1, 0));
            swap(board[i][j], board[i][j + 1]);
        }
        if (i + 1 < N) {
            swap(board[i][j], board[i + 1][j]);
            ans = max(ans, cnt(i, 0, 0, 1));
            ans = max(ans, cnt(i + 1, 0, 0, 1));
            ans = max(ans, cnt(0, j, 1, 0));
            swap(board[i][j], board[i + 1][j]);
        }
    }
    cout << ans;
    return 0;
}