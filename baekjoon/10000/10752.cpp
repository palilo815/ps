#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int M = 15;

char board[M][M];
int DP[M][M];

int main() {
    int R, C; scanf("%d %d", &R, &C);
    loop(i, R) {
        getchar();
        loop(j, C) board[i][j] = getchar();
    }

    DP[0][0] = 1;
    loop(x, R) loop(y, C)
        for (int X = x + 1; X < R; ++X) for (int Y = y + 1; Y < C; ++Y)
            if (board[X][Y] != board[x][y])
                DP[X][Y] += DP[x][y];
    printf("%d", DP[R - 1][C - 1]);
    return 0;
}