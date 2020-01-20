#include <stdio.h>

int main()
{
    double a, b, c, m;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &m);
    printf("%.8lf", ((a * a * (b - m)) + c * c * m) / b - m * (b - m));
    return 0;
}