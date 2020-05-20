#include <cstdio>
#define REP(i,s,e) for(int i=s;i<=e;++i)

const int M = 201;
const int mod = 1000007;

int DP[M][M];

int main() {
    int col, row, mc, mr;
    scanf("%d %d %d %d", &col, &row, &mc, &mr);

    DP[1][1] = 1;
    REP(r, 1, mr) REP(c, 1, mc) {
        DP[r][c] += DP[r - 1][c] + DP[r][c - 1];
        DP[r][c] %= mod;
    }

    DP[mr - 1][mc] = DP[mr][mc - 1] = 0;
    REP(r, mr, row) REP(c, mc, col) {
        DP[r][c] += DP[r - 1][c] + DP[r][c - 1];
        DP[r][c] %= mod;
    }

    printf("%d", DP[row][col]);
    return 0;
}