#include <stdio.h>

int main()
{
    int a, b; scanf("%d %d", &a, &b);
    printf("%d", a / b);
    putchar('.');
    a %= b;
    for (int i = 0; i < 10; ++i) {
        a *= 10;
        printf("%d", a / b);
        a %= b;
    }
    return 0;
}