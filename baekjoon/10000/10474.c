#include <stdio.h>

int main()
{
    int a, b;
    while (1) {
        scanf("%d %d", &a, &b);
        if (b == 0) break;
        printf("%d %d / %d\n", a / b, a % b, b);
    }
    return 0;
}