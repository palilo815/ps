#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
const int max_N = 100;

int DP[max_N + 1];
int main()
{
    loop(i, 101) DP[i] = i * i;
    int N;
    while (1) {
        scanf("%d", &N);
        if (N == 0) break;
        int ans = 0;
        loop(i, N + 1) ans += DP[i];
        printf("%d\n", ans);
    }
    return 0;
}