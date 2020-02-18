#include <stdio.h>

const int mod = 1000000007;

int main()
{
    int N; scanf("%d", &N);
    N += 2;
    int ans = 1;
    while (N--) ans = ans * 2 % mod;
    ans -= 5;
    if (ans < 0) ans += mod;
    printf("%d", ans);
    return 0;
}