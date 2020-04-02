#include <cstdio>
#define LOOP(i,n) for(int i=1;i<=n;++i)
const int MAX = 1000;

int DP[MAX + 1][MAX + 1];
inline int min(int a, int b, int c) {
    if (a > b) a = b;
    return a < c ? a : c;
}
int main() {
    while (1) {
        int row, col; scanf("%d %d", &row, &col);
        if (!row) break;
        int ans = 0;
        LOOP(i, row) LOOP(j, col) scanf("%d", &DP[i][j]);
        LOOP(i, row) LOOP(j, col) if (DP[i][j]) {
            DP[i][j] = min(DP[i - 1][j - 1], DP[i - 1][j], DP[i][j - 1]) + 1;
            if (ans < DP[i][j]) ans = DP[i][j];
        }
        printf("%d\n", ans);
    }
    return 0;
}