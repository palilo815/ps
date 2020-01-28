#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (c % 2) a ^= b;
    printf("%d", a);
    return 0;
}