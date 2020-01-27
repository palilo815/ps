#include <stdio.h>

int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("Case %d:", t);
        if (a / b) printf(" %d", a / b);
        if (a % b) printf(" %d/%d", a % b, b);
        if (a == 0) printf(" 0");
        putchar('\n');
    }
    return 0;
}