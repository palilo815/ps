#include <stdio.h>

int main()
{
    int T, Exp, arr[101];
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d", &Exp);
        for (int i = Exp; i >= 0; --i)
            scanf("%d", &arr[i]);
        printf("Case %d: %d", t, Exp - 1);
        for (int i = Exp; i > 0; --i)
            printf(" %d", arr[i] * i);
        putchar('\n');
    }
    return 0;
}