#include <stdio.h>

int main()
{
    double k, d1, d2, h;
    scanf("%lf %lf %lf", &k, &d1, &d2);
    double tmp = (d1 - d2) / 2;
    h = k * k - tmp * tmp;
    printf("%.8lf", h);
    return 0;
}