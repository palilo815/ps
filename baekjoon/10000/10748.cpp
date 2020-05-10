#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int M = 100;
const int max_K = 10001;
const int mod = 1000000007;

int board[M][M];
int DP[M][M];

int main() {
    int R, C, K; scanf("%d %d %d", &R, &C, &K);
    loop(i, R) loop(j, C) scanf("%d", &board[i][j]);

    DP[0][0] = 1;
    loop(x, R) loop(y, C)
        for (int X = x + 1; X < R; ++X) for (int Y = y + 1; Y < C; ++Y)
            if (board[X][Y] != board[x][y])
                DP[X][Y] = (DP[X][Y] + DP[x][y]) % mod;
    printf("%d", DP[R - 1][C - 1]);
    return 0;
}