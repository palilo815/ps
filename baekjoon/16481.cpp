#include <stdio.h>

int main()
{
    int r1, r2, r3;
    scanf("%d %d %d", &r1, &r2, &r3);
    printf("%.8lf", 1.0 * r1 * r2 * r3 / (r1 * r2 + r2 * r3 + r3 * r1));
    return 0;
}