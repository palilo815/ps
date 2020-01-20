#include <stdio.h>

int main()
{
    double a, b, c, d;
    scanf("%lf %lf %lf", &a, &b, &c);
    printf("%.8lf", a * c / b);
    return 0;
}