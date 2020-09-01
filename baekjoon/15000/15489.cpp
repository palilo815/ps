#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

int pas[30][30];

int main() {
    int R, C, W; scanf("%d%d%d", &R, &C, &W);
    int sr = R - C, sc = C - 1;

    loop(i, 30) loop(j, 30 - i) {
        pas[i][j] = (i && j) ? (pas[i - 1][j] + pas[i][j - 1]) : 1;
    }

    int ans = 0;
    for (int i = sr, len = W; len; ++i, --len)
        for (int j = sc; j < sc + len; ++j)
            ans += pas[i][j];
    printf("%d", ans);
    return 0;
}