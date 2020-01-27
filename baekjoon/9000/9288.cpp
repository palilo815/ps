#include <stdio.h>

int main()
{
    int T, n;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        scanf("%d", &n);
        printf("Case %d:\n", i);
        for (int a = 1; a <= n / 2; ++a) {
            if (n - a > 6) continue;
            printf("(%d,%d)\n", a, n - a);
        }
    }
    return 0;
}