#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int board[10][10];
int N, ans;

void check(int r, int c, int val) {
    while (r < N - 1 && c < N - 1)
        board[++r][++c] += val;
}
void solve(int cnt, int pos) {
    if (cnt > ans) ans = cnt;
    if (cnt + (2 * N - 1 - pos) <= ans) return;
    int r = 0, c = pos;
    if (c >= N) {
        r = c - N + 1;
        c = N - 1;
    }
    while (r < N && c >= 0) {
        if (!board[r][c]) {
            check(r, c, 1);
            solve(cnt + 1, pos + 1);
            check(r, c, -1);
        }
        ++r, --c;
    }
    solve(cnt, pos + 1);
}
int main() {
    scanf("%d", &N);
    loop(i, N) loop(j, N) scanf("%d", &board[i][j]);
    loop(i, N) loop(j, N) board[i][j] = 1 - board[i][j];
    solve(0, 0);
    printf("%d", ans);
    return 0;
}