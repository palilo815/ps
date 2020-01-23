#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int max_N = 1000;

int DP[max_N + 1][max_N + 1];
int main()
{
    int row, col;
    scanf("%d %d", &row, &col);
    LOOP(i, row) LOOP(j, col)
        scanf("%1d", &DP[i][j]);

    int ans = 0;
    LOOP(i,row) LOOP(j,col)
        if (DP[i][j]) {
            int tmp = min(DP[i - 1][j], DP[i][j - 1]);
            tmp = min(tmp, DP[i - 1][j - 1]);
            DP[i][j] = 1 + tmp;
            ans = max(DP[i][j], ans);
        }
    printf("%d", ans * ans);
    return 0;
}