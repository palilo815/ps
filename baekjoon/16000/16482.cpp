#include <stdio.h>

int main()
{
    int a, b, c, AF, BD;
    scanf("%d %d %d %d %d", &a, &b, &c, &AF, &BD);
    double tmp = 1.0 * (c - AF) * (a - BD) / AF / BD;
    printf("%.8lf", b * tmp / (1 + tmp));
    return 0;
}