#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int N, TC = 0;
    while (scanf("%d", &N)) {
        if (N == 0) break;
        int ans = 0;
        loop(row, N) loop(col, row + 1) {
            int x; scanf("%d", &x);
            if (col == 0 || row == N - 1 || row == col) ans += x;
        }
        printf("Case #%d:%d\n", ++TC, ans);
    }
    return 0;
}